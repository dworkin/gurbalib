void usage() {
   string *lines;

   lines = ({ "Usage: mkdir [-h] DIR" });
   lines += ({ " " });
   lines += ({ "mkdir allows you to make a directory named DIR." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "mkdir test" });
   lines += ({ "mkdir /tmp/test" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, diff, edit, ls, more, mkdir, pwd, rm, tail" });

   this_player()->more(lines);
}

void main(string arg) {
   string file;

   if (!arg || arg == "") {
      usage();
      return;
   }
   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   file = normalize_path(arg, this_player()->query_env("cwd"));
   if (!file || file == "") {
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
