void usage() {
   string *lines;

   lines =({ "Usage: rm [-h] FILE" });
   lines += ({ "Remove a file or directory FILE." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\trm /tmp/sirdude.txt" });
   lines += ({ "\trm example.c" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, diff, edit, ls, more, mkdir, pwd, tail" });

   this_player()->more(lines);
}

void main(string arg) {
   string file;

   if (!arg || arg == "") {
      write("Please specify filename to rm.");
      return;
   }
   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   file = normalize_path(arg, this_player()->query_env("cwd"));
   if (!file || file == "") {
      write(arg + ": Permission denied.\n");
      return;
   }

   if (file_exists(file) == -1) {
      if (!remove_dir(file)) {
	 write(arg + ": Not empty.\n");
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
