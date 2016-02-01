inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: indent [-h] FILE" });
   lines += ({ " " });
   lines += ({ "This function uses the default editor's built in indent " +
      "feature \":I\"" });
   lines += ({ "to make your code look pretty.  It's not the end all of " +
      "pretty printers, " });
   lines += ({ "but it's better than nothing.  For a more serious effort see " +
      "the included " });
   lines += ({ "auxillary script: scripts/indent_it provided with the " +
      "mudlib. " });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tindent myfile.c" });

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
   add_also("wiz", "ls");
   add_also("wiz", "more");
   add_also("wiz", "mkdir");
   add_also("wiz", "pwd");
   add_also("wiz", "rm");
   add_also("wiz", "tail");
}

static void main(string str) {
   string tmp;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   str = normalize_path(str, this_player()->query_env("cwd"));

   if (file_exists(str) < 1) {
      write("File not found.\n");
      return;
   }

   editor("edit " + str);
   editor("set sw=3");
   editor("I");

   tmp = editor("wq!");

   if (tmp) {
     write("Indenting " + str + "\n");
     write(tmp);
   } else {
     write("Error Indenting " + str + "\n");
   } 
}
