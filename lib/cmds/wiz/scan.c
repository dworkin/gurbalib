void usage() {
   write("scan [-h] [OBJ]\n");
   write("Print a list of objects in the current room.\n");
   write("If OBJ is specified list the inventory of object OBJ\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: status\n");
}

void main(string str) {
   object where;
   object *objs;
   int i;

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (str) {
      where = this_player()->query_environment()->present(str);

      if (!where) {
	 where = this_player()->present(str);
      }
   } else {
      where = this_environment();
   }

   if (!where) {
      write("Cannot find: " + str + "\n");
      return;
   }

   write("Scanning \"" + object_name(where) + "\":");
   objs = where->query_inventory();
   if (objs) {
      for (i = 0; i < sizeof(objs); i++) {
         write("\"" + object_name(objs[i]) + "\"");
      }
   } else {
      write("No items in that object.\n");
   }
}
