void usage() {
   string *lines;

   lines = ({ "Usage: tail [-h] [file]" });
   lines += ({ " " });
   lines += ({ "Show the tail end of a file " + "(print it to the screen)." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\ttail void.c" });
   lines += ({ "\ttail /domains/required/rooms/void.c" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, diff, edit, ls, more, mkdir, pwd, rm" });

   this_player()->more(lines);
}

void main(string arg) {
   string file;
   string *tmp;
   string *lines;
   int num_lines, start, i, where;

   if (!arg || arg == "") {
      arg = this_environment()->file_name();
   }
   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   file = normalize_path(arg, this_player()->query_env("cwd"));

   if (file_exists(file) < 1) {
      write(arg + ": File not found.");
      return;
   }

   tmp = explode(read_file(file), "\n");
   lines = ( { } );
   for (i = 0; i < sizeof(tmp); i++) {
      if (strlen(tmp[i]) > 79) {
	 /* Big line. Break it up. */
	 where = 0;
	 while (where < strlen(tmp[i])) {
	    if (where + 79 < strlen(tmp[i])) {
	       lines += ( {
		  tmp[i][where..where + 78]}
	       );
	       where += 79;
	    } else {
	       lines += ( { tmp[i][where..] } );
	       where = strlen(tmp[i]);
	    }
	 }
      } else {
	 lines += ( { tmp[i] } );
      }
   }

   num_lines = sizeof(lines);
   start = num_lines - 20;
   if (start < 0) {
      start = 0;
   }
   for (i = start; i < num_lines; i++) {
      write(lines[i]);
   }
}
