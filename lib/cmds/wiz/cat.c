void usage() {
   string *lines;

   lines = ({ "Usage: cat [-h] [file]" });
   lines += ({ " " });
   lines += ({ "cat allows a wizard to concatenate a file " +
      "(print it to the screen)." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tcat void.c" });
   lines += ({ "\tcat /domains/required/rooms/void.c" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cd, cp, diff, edit, ls, more, mkdir, pwd, " +
      "rm, tail" });

   this_player()->more(lines);
}

void main(string file) {
   string *lines;
   string name;
   int i;

   if (!file || file == "") {
      file = this_player()->query_env("cwf");
   } else if (sscanf(file, "-%s", file)) {
      usage();
      return;
   }

   name = normalize_path(file, this_player()->query_env("cwd"));
   if (!name || name == "") {
      write("Access denied.\n");
      return;
   }

   if (file_exists(name) == 1) {
      lines = explode(read_file(name), "\n");
      for (i = 0; i < sizeof(lines); i++) {
	 out(lines[i] + "\n");
      }
   } else {
      write("That file doesn't exist.");
   }
}
