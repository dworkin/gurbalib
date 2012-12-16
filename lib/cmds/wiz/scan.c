void usage() {
   string *lines;

   lines = ({ "scan [-h] [OBJ]" });
   lines += ({ " " });
   lines += ({ "Print a list of objects in the current room." });
   lines += ({ "If OBJ is specified list the inventory of object OBJ" });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tscan" });
   lines += ({ "\tscan rat" });
   lines += ({ "See also:" });
   lines += ({ "\tdate, status, time" });

   this_player()->more(lines);
}

void main(string str) {
   object where;
   object *objs;
   int i, done;

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!str || str == "") {
      where = this_environment();
   } else {
      where = this_player()->query_environment()->present(str);

      if (!where) {
	 where = this_player()->present(str);
      }
   }

   if (!where) {
      write("Cannot find: " + str + "\n");
      return;
   }

   write("Scanning \"" + object_name(where) + "\":");
   objs = where->query_inventory();
   if (objs) {
      done = 0;
      for (i = 0; i < sizeof(objs); i++) {
         done = 1;
         write("\"" + object_name(objs[i]) + "\"");
      }
      if (!done) {
         write("No items in that object.\n");
      }
   } else {
      write("No items in that object.\n");
   }
}
