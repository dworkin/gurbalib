int warn, error;

void usage() {
   write("Usage: check [-h] FILENAME\n");
   write("Check the supplied file, FILENAME.\n");
   write("If FILENAME is a directory check all files in that directory.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: update, clone\n");
}

void warn(string str) {
   write("Warning: " + str);
   warn+=1;
}
void error(string str) {
   write("Warning: " + str);
   error+=1;
}

string add_dotc(string input) {
   string str;

   str = input;
   if (!str || str == "") return "";

   if (strlen(str) > 2) {
      if (str[strlen(str) - 2] == '.' && str[strlen(str) - 1] == 'c') {
         /* were good do nothing... */
      } else {
         str = str + ".c";
      }
   }
   return str;
}

string get_what(string str) {
   string path;

   path = this_player()->query_env("cwd");
   path = normalize_path(str, path);
   if (file_exists(path)) return path;
   path = add_dotc(path);
   return path;
}

void check_remote_exit(string room, string exit, string filename) {
   object obj;
   string tmp, myexit;

   if (file_exists(room)) {

      obj = find_object(room);

      if (!obj) {
         obj = compile_object(room);
         obj->setup();
         obj->setup_mudlib();
      }
   }

   if (!obj) {
      error("Unable to load room : " + room + "\n");
      return;
   }

  myexit = invert_exit(exit);
  tmp = obj->query_exit(myexit);
  tmp = add_dotc(tmp);

  if (!tmp || tmp == "") {
     warn("No reverse exit: " + obj->base_name() + 
        "(" + myexit + ")\n");
  } else if (tmp != filename) {
     warn("Reverse exit " + obj->base_name() + ":(" + myexit + ")\n" +
        "Points at: " + tmp + " not " + filename + ".\n");
  }
}

void check_exits(object obj, mapping myexits) {
   string *indices;
   string exit, filename, exitfile;
   int x, len;

   indices = map_indices(myexits);

   x = sizeof(indices) -1;
   while (x > -1) {
      exitfile = myexits[indices[x]];
      exitfile = add_dotc(exitfile);

      write("Checking exit: " + indices[x] + " " + exitfile + "\n");

      if (!file_exists(exitfile)) {
         warn("Exit: " + indices[x] + ":" + 
            myexits[exitfile] + " does not exist.\n");
      } else if (invert_exit(indices[x]) != "unknown") {
         filename = obj->base_name();
         filename = add_dotc(filename);

         check_remote_exit(exitfile, indices[x], filename);

      } else {
	warn("Nonstandard exit: " + exitfile + " no further checks.\n");
      }
      x = x - 1;
   }
}

void do_room_check(object obj) {
   mapping myexits;
   write("Doing room check\n");

   myexits = obj->query_exits();
   check_exits(obj,myexits);

   myexits = obj->query_hidden_exits();
   check_exits(obj,myexits);

   myexits = obj->query_room_commands();
}

void do_monster_check(object obj) {
   string tmp;

   write("Doing monster check\n");

   tmp = obj->query_name();
   if (!tmp || tmp == "") warn("Monster has no name.\n");
   tmp = obj->query_brief();
   if (!tmp || tmp == "") warn("Monster has no brief description.\n");
   tmp = obj->query_long();
   if (!tmp || tmp == "") warn("Monster has no long description.\n");

   if (obj->is_gettable()) warn("Living object is gettable.\n");
}

void do_object_check(object obj) {
   string tmpstr;
   write("Doing object check\n");

   tmpstr = obj->query_brief();
   if (!tmpstr || tmpstr == "") warn("No brief description.\n");

   tmpstr = obj->query_long();
   if (!tmpstr || tmpstr == "") warn("No long description.\n");

   if (obj->is_gettable() && (obj->query_weight() < 1))
      warn("Object gettable and weight < 1\n");
   if (obj->is_gettable() && (obj->query_value() < 1))
      warn("Object gettable and value < 1\n");
}

void do_check(string str) {
   string what;
   object obj;

   what = get_what(str);
   if (file_exists(what) == -1) {
      write("Checking directories unsupported currently: " + what + "\n");
   } else {
      if (file_exists(what) == 1) {
         write("Looking at file: " + what + "\n");

         obj = compile_object(what);
         obj->setup();
         obj->setup_mudlib();

         if (obj) {
            if (obj->is_room()) {
               do_room_check(obj);
            } else if (obj->is_living()) {
               do_monster_check(obj);
            } else {
               do_object_check(obj);
            }
         } else {
            error("Unable to compile: " + str + "\n");
         }
      }
   }
}

void main(string str) {
   string *files;
   int x, max;

   if (!str || str == "") {
      usage();
      return;
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   files = explode(str," ");
   if (!files) files = ({ str });
   max = sizeof(files);
   for(x=0;x<max;x++) {
      warn =0;
      error = 0;
      do_check(files[x]);
      write("Errors: " + error + " Warnings: " + warn + "\n");
   }
}
