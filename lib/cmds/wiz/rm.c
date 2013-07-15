void usage() {
   string *lines;

   lines =({ "Usage: rm [-h] FILE" });
   lines += ({ " " });
   lines += ({ "Remove a file or directory FILE." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\trm /tmp/sirdude.txt" });
   lines += ({ "\trm example.c" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, cp, diff, edit, ls, more, mkdir, pwd, " +
      "tail" });

   this_player()->more(lines);
}

int recursive_remove_dir(string file) {

   /* XXX Do this so you can recursively remove a directory... */

   write(file + ": Not empty.\n");
   return 0;
}

void main(string arg) {
   string file;

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (!arg || (arg == "")) {
      write("Please specify filename to rm.");
      return;
   }

   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   file = normalize_path(arg, this_player()->query_env("cwd"));
   if (!file || (file == "")) {
      write(arg + ": Permission denied.\n");
      return;
   }

   if (file_exists(file) == -1) {
      if (!remove_dir(file)) {
         recursive_remove_dir(file));
      } else {
	 write("Deleted.\n");
      }
   } else if (file_exists(file)) {
      if (!remove_file(file)) {
	 write(arg + ": Unable to delete.\n");
      }
   } else {
      write(arg + ": Not found.\n");
   }
}
