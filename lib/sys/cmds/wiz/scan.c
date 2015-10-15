inherit M_COMMAND;

string *usage(void) {
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

   return lines;
}

static void main(string str) {
   object where, *objs;
   int i, sz, done;

   if (empty_str(str)) {
      where = this_environment();
   } else if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
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
      sz = sizeof(objs);
      for (i = 0; i < sz; i++) {
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
