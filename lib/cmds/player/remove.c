void usage() {
   write("Usage: remove [-h] [all|OBJ]\n");
   write("Allows you to remove a given object OBJ, that you are " +
      "currently wearing or wielding.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tRemove everything you are wearing and wielding.\n");
   write("Examples:\n");
   write("\tremove helmet\n");
   write("\tremove all\n");
   write("See also: get, drop, put, wear, wield\n");
}

void do_remove(object obj, int loud) {
   string slot;
   object worn;

   if (!obj) {
      if (loud) {
         write("what are you trying to remove?");
      }
      return;
   }

   if (obj->is_worn()) {
      if (obj->is_cursed()) {
         this_player()->targetted_action("$N $vtry to remove $o, but $vfumble.",
            nil, obj);
         write("Strange... It won't come off.\n");
         return;
      }
   } else if (obj->is_wielded()) {
      if (obj->is_cursed()) {
         this_player()->targetted_action("$N $vtry to remove $o, but $vfumble.",
            nil, obj);
         write("Strange... It won't come off.\n");
         return;
      }
   } else {
      write("You are not wearning or wielding that.\n");
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
