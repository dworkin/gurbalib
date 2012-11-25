void usage() {
   write("Usage: close [-h] [all|OBJ]\n");
   write("Allows you to open a given object OBJ.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tOpen everything you can.\n");
   write("See also: open.\n");
}

void do_open(object obj, int loud) {
   string slot;
   object worn;

   if (loud && !obj) {
      write("what are you trying to open?");
   }

   if (!obj->is_openable() && loud) {
      write("You can't open the " + obj->query_id() + ".");
      return;
   }
   obj->do_open(this_player());
}

void main(string str) {
   object obj;
   object *inv;
   int i, max;

   if (!str || str == "") {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (str == "all") {
      inv = this_player()->query_environment()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_open(inv[i],0);
      }

      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_open(inv[i],0);
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      obj = this_player()->query_environment()->present(lowercase(str));
   }
   do_open(obj,1);
}
