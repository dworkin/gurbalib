void usage() {
   write("Usage: check [-h] FILENAME\n");
   write("Check the supplied file, FILENAME.\n");
   write("If FILENAME is a directory check all files in that directory.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: update, clone\n");
}

string get_what(string str) {
   string path;

   path = this_player()->query_env("cwd");

   if (strlen(str) > 2) {
      if (str[strlen(str) - 2] == '.' && str[strlen(str) - 1] == 'c') {
	 // were good do nothing...
      } else {
	 str = str + ".c";
      }
   }

   path = normalize_path(str, path);

   return path;
}

void main(string str) {
   string *files;

   if (!str || str == "") {
      usage();
      return;
   }
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   files = explode();

}
