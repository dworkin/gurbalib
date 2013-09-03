inherit M_COMMAND;

void usage() {
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
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, cp, diff, edit, ls, more, mkdir, pwd, " +
      "rm, tail" });

   this_player()->more(lines);
}

static void main(string str) {
   string tmp;

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
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
