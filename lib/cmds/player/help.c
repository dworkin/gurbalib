inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: help [-h] [TOPIC]" });
   lines += ({ "" });
   lines += ({ "Get basic information on: TOPIC" });
   lines += ({ "Current topics:" });
   lines += ({ "\tnewbie       If your new to the mud start here." });
   lines += ({ "\tcomm         Basics on communication on the mud." });
   lines += ({ "\trules        Some basic rules you should be familiar with." 
      });
   lines += ({ "\tbugs         How to report bugs you may find." });
   lines += ({ "\ttime         How does time work on the mud?" });
   lines += ({ "\tchan         Another way to communicate." });

   if (query_wizard(this_player())) {
      lines += ({ "\twizard       If you are a wizard start here" });
   }

   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\thelp newbie" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "cmds");

   add_also("wiz", "man");
}

int show_help_for_command(string cmd) {
   string tmp;

   tmp = cmd + " -h";
   return call_other(this_player(), "do_game_command", tmp);
}

string *get_data(string filename) {
   string *lines, *tmp;
   int i, sz, where, len, width;

   width = this_player()->query_width();
   tmp = explode(read_file(filename), "\n");
   sz = sizeof(tmp);

   lines = ({ });

   for (i = 0; i < sz; i++) {
      if (strlen(tmp[i]) > width) {
         /* Big line. Break it up. */
         where = 0;
         len = strlen(tmp[i]);
         while (where < len) {
            if (where + width < len) {
               lines += ( { tmp[i][where..(where + width - 1)] } );
               where += width;
            } else {
               lines += ( { tmp[i][where..] } );
               where = len;
            }
         }
      } else {
         lines += ( { tmp[i] } );
      }
   }
   return lines;
}

int show_help(string filename) {
   string blah, *lines;
   int i, sz;

   if (file_exists(filename) < 1) {
      return 0;
   }

   lines = ( { "Help for " + capitalize(filename) + "." } );

   blah = "";
   sz = strlen(lines[0]);
   for (i = 0; i < sz; i++) {
      blah += "-";
   }
   lines += ( { blah } );

   lines += get_data(filename);

   this_player()->more(lines);
   return 1;
}

static void main(string arg) {
   string file;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(arg) || (arg == "help")) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(arg, "-%s", arg)) {
      this_player()->more(usage());
      return;
   }

   file = normalize_path(arg, "/doc/help/");

   if (strcmp(file[0..9], "/doc/help/") != 0) {
      write("Invalid help file.\n");
      return;
   }

   if (show_help(file)) {
      return;
   }

   if (query_wizard(this_player())) {
      file = normalize_path(arg, "/doc/help/wiz/");
      if (show_help(file)) {
         return;
      }
   }

   if (show_help_for_command(arg)) {
      return;
   }

   write(capitalize(arg) + ": Unknown help topic.");
   if (query_wizard(this_player())) {
      write("Try one of the following for more info:\n");
      write("\tman " + arg + "\n");
      write("\t" + arg + " -h\n");
   } else {
      write("If " + arg + " is a command, for more info try: " + 
         arg + " -h\n");
   }
   LOG_D->write_log("help", this_player()->query_Name() +
      " on " + ctime(time()) + ": " + arg + "\n");
   return;
}
