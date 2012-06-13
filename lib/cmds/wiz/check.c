mapping exits;

void usage() {
   write("Usage: check [-h] FILENAME\n");
   write("Check the supplied file, FILENAME.\n");
   write("If FILENAME is a directory check all files in that directory.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: update, clone\n");
}

void setup_exits() {
   exists["north"] = "south";
   exists["south"] =  "north";
   exists["east"] = "west";
   exists["west"] = "east";
   exists["up"] = "down";
   exists["down"] = "up";
   exists["northwest"] = "southeast";
   exists["southeast"] = "northwest";
   exists["northeast"] = "southwest";
   exists["southwest"] = "northeast";
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

void do_check(string str) {
   if (is_directory(str)) {
   } else {
   }
}

void main(string str) {
   string *files;
   int x, max;

   if (!str || str == "") {
      usage();
      return;
   }
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   files = explode(str," ");
   if (!files) files = ([ str ]);
   max = sizeof(files);
   for(x=0;x<max;x++) {
      do_check(files[x]);
   }
}
