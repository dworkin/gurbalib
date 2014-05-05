inherit M_COMMAND;

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
   lines += ({ "\tbrowse, cat, cd, cp, diff, edit, indent, ls, more, " +
      "mkdir, pwd, tail" });

   this_player()->more(lines);
}

/* This doesn't totally work right fix it XXX */
int recursive_remove_dir(string file) {
   mixed *files;
   string *names;
   int x, maxx;
   string path;

write("Removing files from dir: " + file + "\n");
   files = get_dir(file);
   names = files[0];

   maxx = sizeof(names);
   for (x=0; x<maxx; x++) {
      path = file + "/" + names[x];
write("Trying to remove " + x + "/" + maxx + " : " + path + "\n");

      if (file_exists(path) == -1) {
write("Woo here \n");
         recursive_remove_dir(path);
      } else if (file_exists(path) == 0) {
         write("Error no such file " + path + "\n");
      } else {
         if (!remove_file(path)) {
	    write(path + ": Unable to delete.\n");
         } else {
            write("Removing: " + path + "\n");
         }
      }
   }

   if (remove_dir(file)) {
      return 1;
   } else {
      write(file + ": not empty.\n");
      return 0;
   }
}

static void main(string arg) {
   string file;

   if (empty_str(arg)) {
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
         recursive_remove_dir(file);
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
