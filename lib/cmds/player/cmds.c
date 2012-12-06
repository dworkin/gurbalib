int col;
string *lines;

void usage() {
   string flags;
   string *lines;

   flags = "player|verb";

   if (query_wizard(this_player()))
      flags += "|wiz";
   if (query_admin(this_player()))
      flags += "|admin";

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
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tman, help" });
   } else {
      lines += ({ "\thelp" });
   }

   this_player()->more(lines);
}

void show_cmds(string dir) {
   string *names;
   mapping cmds;
   int c, d, sz;
   string *files;
   int i;

   cmds = ([]);
   files = get_dir(dir + "/*.c")[0];
   for (i = sizeof(files) - 1; i >= 0; i--) {
      cmds[files[i][..strlen(files[i]) - 3]] = dir;
   }

   names = map_indices(cmds);

   lines += ( { "Commands: " + dir } );

   for (d = 0, sz = sizeof(names); d < sz; d += col) {
      int colnum;
      string line;

      line = "";

      for (colnum = 0; colnum < col; colnum++) {
	 if (d + colnum < sz) {
	    line += (names[d + colnum] +
	       (col == 1 ? " (" + cmds[names[d + colnum]] + ")" : "") +
	       "                                             " +
	       "                         ")[0..(70 / col)];
	 }
      }
      lines += ( { line } );
   }

}

void main(string str) {
   string *path;
   int c, cmax;
   mixed width;

   width = this_player()->query_env("width");
   if (!intp(width) || width < 2)
      width = DEFAULT_WIDTH;

   lines = ( { } ); 

   if (str == "-v") {
      col = 1;
   } else {
      col = 4;
      if (str && str != "") {
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
		  show_cmds("/cmds/wiz");
	       } else {
		  usage();
	       }
	       break;
	    case "admin":
	       if (query_admin(this_player())) {
		  show_cmds("/kernel/cmds/admin");
	       } else {
		  usage();
	       }
	       break;
            case "emote":
            case "emotes":
               lines += EMOTE_D->show_emote("",width);
               break;
            case "fighter":
            case "fighters":
		  show_cmds("/cmds/guild/fighter");
               break;
	    default:
	       usage();
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

   show_cmds("/cmds/verb");

   lines += EMOTE_D->show_emote("",width);

   this_player()->more(lines);
}
