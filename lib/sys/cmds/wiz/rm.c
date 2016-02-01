inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: rm [-h] FILE" });
   lines += ({ " " });
   lines += ({ "Remove a file or directory FILE." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\trm /tmp/sirdude.txt" });
   lines += ({ "\trm example.c" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "browse");
   add_also("wiz", "cat");
   add_also("wiz", "cd");
   add_also("wiz", "cp");
   add_also("wiz", "diff");
   add_also("wiz", "edit");
   add_also("wiz", "indent");
   add_also("wiz", "ls");
   add_also("wiz", "more");
   add_also("wiz", "mkdir");
   add_also("wiz", "pwd");
   add_also("wiz", "tail");
}

int recursive_remove_dir(string path) {
   mixed *files;
   string tfile, *names;
   int x, maxx;

   files = get_dir(path + "/*");
   names = files[0];

   maxx = sizeof(names);
   for (x = 0; x < maxx; x++) {
      tfile = path + "/" + names[x];

      if (file_exists(tfile) == -1) {
         recursive_remove_dir(tfile);
      } else if (file_exists(tfile) == 0) {
         write("Error no such file " + tfile + "\n");
      } else {
         if (!remove_file(tfile)) {
            write("Unable to delete:" + tfile + "\n");
         } else {
            write("Removing: " + tfile + "\n");
         }
      }
   }

   if (remove_dir(path)) {
      return 1;
   } else {
      write(path + ": not empty.\n");
      return 0;
   }
}

static void main(string arg) {
   string file;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(arg)) {
      write("Please specify filename to rm.");
      return;
   }

   if (sscanf(arg, "-%s", arg)) {
      this_player()->more(usage());
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
