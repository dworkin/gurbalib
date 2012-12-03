void usage() {
   write("Usage: help [-h] [TOPIC]\n");
   write("Get basic information on: TOPIC\n");
   write("Current topics:\n");
   write("\tnewbie       If your new to the mud start here.\n");
   write("\tcomm         Basics on communication on the mud.\n");
   write("\trules        Some basic rules you should be familar with.\n");
   write("\tmultis       Our stance on multiple chars per person.\n");
   write("\troleplaying  Some suggestions.\n");
   write("\tabuse        What happens if you abuse the rules.\n");
   write("\tbugs         How to report bugs you may find.\n");
   write("\tcontact      How can you get ahold of someone if you need help.\n");
   write("\ttime         How does time work on the mud?\n");
   write("\tchannels     Another way to communicate.\n");

   if (query_wizard(this_player())) {
      write("\twizard       If you are a wizard start here\n");
   }

   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\thelp newbie\n");

   if (query_wizard(this_player())) {
      write("See also: cmds, man\n");
   } else {
      write("See also: cmds\n");
   }
}

void show_file(string filename) {
   string *tmp;
   string blah;
   string *lines;
   int i, len, where;
   mixed width;

   width = this_player()->query_env("width");
   if (!intp(width) || width < 2)
      width = DEFAULT_WIDTH;

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
}

void main(string arg) {
   string file;
   if (!arg || arg == "" || arg == "help") {
      usage();
      return;
   }

   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   arg = lowercase(arg);

   file = normalize_path(arg, "/doc/help/");

   if (file_exists(file) < 1) {
      if (query_wizard(this_player())) {
	 file = normalize_path(arg, "/doc/help/wiz/");
	 if (file_exists(file) < 1) {
	    write(capitalize(arg) + ": Unknown help topic.");
	    LOG_D->write_log("help", this_player()->query_Name() +
	       " on " + ctime(time()) + ": " + arg + "\n");
	    return;
	 }
      } else {
	 write(capitalize(arg) + ": Unknown help topic.");
	 LOG_D->write_log("help", this_player()->query_Name() +
	    " on " + ctime(time()) + ": " + arg + "\n");
	 return;
      }
   }

   show_file(file);
}
