void usage() {
   write("Usage: close [-h] [all|OBJ]\n");
   write("Allows you to close a given object OBJ.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tClose everything you can.\n");
   write("See also: open.\n");
}

void do_close(object obj, int loud) {
   string slot;
   object worn;

   if (!obj) {
      if (loud) {
         write("what are you trying to close?");
      }
      return;
   }

   if (!obj->is_closable()) {
      if (loud) {
         write("You can't close the " + obj->query_id() + ".");
      }
      return;
   }
   obj->do_close(this_player());
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
         do_close(inv[i],0);
      }

      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_close(inv[i],0);
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      obj = this_player()->query_environment()->present(lowercase(str));
   }
   do_close(obj,1);
}
