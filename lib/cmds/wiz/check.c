static mapping exits;

void usage() {
   write("Usage: check [-h] FILENAME\n");
   write("Check the supplied file, FILENAME.\n");
   write("If FILENAME is a directory check all files in that directory.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: update, clone\n");
}

void setup_exits() {
   exits = ([]);
   exits["north"] = "south";
   exits["south"] =  "north";
   exits["east"] = "west";
   exits["west"] = "east";
   exits["up"] = "down";
   exits["down"] = "up";
   exits["northwest"] = "southeast";
   exits["southeast"] = "northwest";
   exits["northeast"] = "southwest";
   exits["southwest"] = "northeast";
}

string get_what(string str) {
   string path;

   path = this_player()->query_env("cwd");

   path = normalize_path(str, path);

   if (file_exists(path)) return path;

   if (strlen(str) > 2) {
      if (str[strlen(str) - 2] == '.' && str[strlen(str) - 1] == 'c') {
         /* were good do nothing... */
      } else {
         str = str + ".c";
      }
   }

   return path;
}

void check_remote_exit(string room, string exit, string filename) {
   object obj;
   string tmp, myexit;

   obj = compile_object(room);
   /* XXX Should we do this if room already exists??? */
   obj->setup();
   obj->setup_mudlib();


   if (!obj) {
      write("Unable to load room : " + room + "\n");
      return;
   }

  myexit = exits[exit];
  tmp = obj->query_exit(myexit);

  if (!tmp || tmp == "") {
     write("Warning: No reverse exit: " + obj->base_name() + 
        "(" + myexit + ")\n");
  } else if (tmp != filename) {
     write("Warning: reverse exit " + obj->base_name() + ":(" + myexit + ")\n");
     write("points at: " + tmp + " not " + filename + ".\n");
  }
}

void check_exits(object obj, mapping myexits) {
   string *indices;
   string exit, filename;
   int x;

   indices = map_indices(myexits);

   x = sizeof(indices) -1;
   while (x > -1) {

      write("Checking exit: " + indices[x] + "\n");

      if (!file_exists(myexits[indices[x]])) {
         write("Warning exit: " + indices[x] + ":" + 
            myexits[indices[x]] + " does not exist.\n");
      } else if (member_map(indices[x],exits)) {
         filename = obj->base_name();
         if (filename[strlen(filename) - 2] == '.' && 
            filename[strlen(filename) - 1] == 'c') {
            /* were good do nothing... */
         } else {
            filename = filename + ".c";
         }
         check_remote_exit(myexits[indices[x]], indices[x], filename);
      } else {
	write("Warning nonstandard exit: " + indices[x] + 
           " no further checks.\n");
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
   if (!tmp || tmp == "") write("Warning: Monster has no name.\n");
   tmp = obj->query_brief();
   if (!tmp || tmp == "") write("Warning: Monster has no brief description.\n");
   tmp = obj->query_long();
   if (!tmp || tmp == "") write("Warning: Monster has no long description.\n");

   if (obj->is_gettable()) write("Warning: Living object is gettable.\n");
}

void do_object_check(object obj) {
   string tmpstr;
   write("Doing object check\n");

   tmpstr = obj->query_brief();
   if (!tmpstr || tmpstr == "") write("Warning: No brief description.\n");

   tmpstr = obj->query_long();
   if (!tmpstr || tmpstr == "") write("Warning: No long description.\n");

   if (obj->is_gettable() && (obj->query_weight() < 1))
      write("Warning: object gettable and weight < 1\n");
   if (obj->is_gettable() && (obj->query_value() < 1))
      write("Warning: object gettable and value < 1\n");
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
            write("Unable to compile: " + str + "\n");
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

   setup_exits();

   files = explode(str," ");
   if (!files) files = ({ str });
   max = sizeof(files);
   for(x=0;x<max;x++) {
      do_check(files[x]);
   }
}
