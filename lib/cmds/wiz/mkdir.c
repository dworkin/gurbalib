void usage() {
   string *lines;

   lines = ({ "Usage: mkdir [-h] DIR" });
   lines += ({ " " });
   lines += ({ "mkdir allows you to make a directory named DIR." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tmkdir test" });
   lines += ({ "\tmkdir /tmp/test" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, cp, diff, edit, inedent, ls, more, pwd, " +
      "rm, tail" });

   this_player()->more(lines);
}

void main(string arg) {
   string file;

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (!arg || (arg == "")) {
      usage();
      return;
   }
   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   file = normalize_path(arg, this_player()->query_env("cwd"));
   if (!file || (file == "")) {
      write("Permission denied.\n");
      return;
   }

   if (!file_exists(file)) {
      if (!make_dir(file)) {
	 write("Unable to create directory.\n");
	 return;
      } else {
	 write("Directory created.\n");
	 return;
      }
   } else {
      write("File or dir already exists.\n");
   }

}
