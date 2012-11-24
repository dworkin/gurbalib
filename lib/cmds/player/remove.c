void usage() {
   write("Usage: remove [-h] [all|OBJ]\n");
   write("Allows you to remove a given object OBJ, that you are " +
      "currently wearing.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tDrop everything you are carring.\n");
   write("See also: get, remove.\n");
}

void do_remove(object obj, int loud) {
   string slot;
   object worn;

   if (loud && !obj) {
      write("what are you trying to remove?");
   }

   if (obj->is_worn() && obj->is_cursed() {
      this_player()->targetted_action("$N $vtry to remove $o, but $vfumble.",
         nil, obj);
      write("Strange... It won't come off.\n");
      return;
   }

   if (!obj->query_worn()) {
      write("Your not wearning that.\n");
      return;
   }

   this_player()->do_remove(obj);
   this_player()->targetted_action(obj->query_remove_message(), nil, obj);
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
      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_remove(inv[i],0);
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   do_remove(obj,1);
}
