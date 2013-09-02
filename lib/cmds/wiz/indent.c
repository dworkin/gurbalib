void usage() {
   string *lines;

   lines = ({ "Usage: indent [-h] FILE" });
   lines += ({ " " });
   lines += ({ "Indents the file specified with the editor's build in indent " +
      "feature." });
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

void main(string str) {
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
