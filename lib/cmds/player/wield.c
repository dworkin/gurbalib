void usage() {
   write("Usage: wield [-h] [all|obj]\n");
   write("Allows you to equip a given object OBJ.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tEquip all available objects.\n");
   write("See also: wield, remove.\n");
}
void do_wield(object obj, int loud) {
   string slot;
   object* wielded;

   if (!obj) {
      if (loud) {
         write("Maybe you should get one first?");
      }
      return;
   }

   if (!obj->is_wieldable()) {
      if (loud) {
         write("You can't wield that.");
      }
      return;
   }

   if (obj->query_wielded() == 1) {
      if (loud) {
         write("You already are wielding that.");
      }
      return;
   }

   wielded = this_player()->query_wielded();

   if (obj->query_wield_type() == "single") {
      if (sizeof(wielded) >= 2) {
         write("Your hands are full.");
         return;
      }
   } else {
      if (sizeof(wielded) != 0) {
         write("You are already wielding something else.");
         return;
      }

   }

   this_player()->do_wield(obj);
   this_player()->targetted_action(obj->query_wield_message(), nil, obj);
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
         do_wield(inv[i],0);
      }
      return;
   }
   obj = this_player()->present(lowercase(str));
   do_wield(obj,1);
}
