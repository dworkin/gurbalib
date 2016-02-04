inherit M_COMMAND;

int col;
string *lines;

string *usage(void) {
   string flags, *lines;

   flags = "player|verb";

   if (query_wizard(this_player())) {
      flags += "|wiz";
   }
   if (query_admin(this_player())) {
      flags += "|admin";
   }

   lines = ({ "Usage: cmds [-h] [-v] [" + flags + "]" });
   lines += ({ "" });
   lines += ({ "cmds lists the various cmds at your disposal." });
   lines += ({ "If you specify a subsection like player it will only list " +
      "player commands, " });
   lines += ({ "instead of all commands you have available." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-e\tInclude emotes." });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-v\tVertical, displays commands one per line." });
   lines += ({ "Examples:" });
   lines += ({ "\tcmds" });
   lines += ({ "\tcmds players" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "help");

   add_also("wiz", "man");
}

static void show_cmds(string dir) {
   string *names, *files;
   mapping cmds;
   int c, d, sz, i;

   cmds = ([]);
   files = get_dir(dir + "/*.c")[0];
   for (i = sizeof(files) - 1; i >= 0; i--) {
      cmds[files[i][..strlen(files[i]) - 3]] = dir;
   }

   names = map_indices(cmds);

   lines += ( { "Commands: " + dir } );

   for (d = 0, sz = sizeof(names); d < sz; d += col) {
      int colnum;
      string line, tmp;

      line = "";

      for (colnum = 0; colnum < col; colnum++) {
         if (d + colnum < sz) {
            if (col == 1) {
               tmp = " (" + cmds[names[d + colnum]] + ")";
            } else {
               tmp = "";
            }

            line += (names[d + colnum] + tmp +
               "                                             " +
               "                         ")[0..(70 / col)];
         }
      }
      lines += ( { line } );
   }

}

static void main(string str) {
   string *path;
   int c, cmax;
   int width;

   width = this_player()->query_width();

   lines = ( { } ); 

   if (!alsos) {
      setup_alsos();
   }

   if (str == "-v") {
      col = 1;
   } else {
      col = 4;
      if (str && (str != "")) {
         switch (str) {
            case "player":
               show_cmds("/cmds/player");
               break;
            case "verb":
               show_cmds("/cmds/verb");
               break;
            case "wiz":
            case "wizard":
               if (query_wizard(this_player())) {
                  show_cmds("/sys/cmds/wiz");
               } else {
                  this_player()->more(usage());
               }
               break;
            case "admin":
               if (query_admin(this_player())) {
                  show_cmds("/sys/cmds/admin");
               } else {
                  this_player()->more(usage());
               }
               break;
            case "emote":
            case "emotes":
               lines += EMOTE_D->show_emote("", width);
               break;
            case "fighter":
            case "fighters":
               show_cmds("/cmds/guild/fighter");
               break;
            default:
               this_player()->more(usage());
               break;
         }
         this_player()->more(lines);
         return;
      }
   }

   path = this_player()->query_path();

   for (c = sizeof(path) - 1; c >= 0; c--) {
      show_cmds(path[c]);
   }

   /* Currently we have none... */
   /* show_cmds("/cmds/verb"); */

   lines += EMOTE_D->show_emote("", width);

   this_player()->more(lines);
}
