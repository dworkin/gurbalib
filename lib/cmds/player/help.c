inherit M_COMMAND;

void usage() {
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
   lines += ({ "See also:" });

   if (query_wizard(this_player())) {
      lines += ({ "\tcmds, man" });
   } else {
      lines += ({ "\tcmds" });
   }

   this_player()->more(lines);
}

int show_help_for_command(string cmd) {
   string tmp;

   tmp = cmd + " -h";
   return call_other(this_player(), "do_game_command", tmp);
}

int show_help(string filename) {
   string *tmp;
   string blah;
   string *lines;
   int i, len, where, width;


   if (file_exists(filename) < 1) {
      return 0;
   }

   width = this_player()->query_width();

   lines = ( { "Help for " + capitalize(filename) + "." } );
   blah = "";
   for (i = 0; i < strlen("Help for " + filename + "."); i++) {
      blah += "-";
   }
   lines += ( { blah } );

   tmp = explode(read_file(filename), "\n");
   for (i = 0; i < sizeof(tmp); i++) {
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

   this_player()->more(lines);
   return 1;
}

static void main(string arg) {
   string file;
   if (empty_str(arg) || (arg == "help")) {
      usage();
      return;
   }

   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   arg = lowercase(arg);

   file = normalize_path(arg, "/doc/help/");
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
   LOG_D->write_log("help", this_player()->query_Name() +
      " on " + ctime(time()) + ": " + arg + "\n");
   return;
}
