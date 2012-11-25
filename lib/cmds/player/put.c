void usage() {
   write("Usage: put [-h] [all|OBJ] [at|in] OBJ2\n");
   write("Allows you to put OBJ inside OBJ2\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tPut everything you are carring in OBJ2.\n");
   write("See also: get, remove.\n");
}

void do_put(object obj1, object obj2, int loud) {
   string slot;
   object worn;

   if (loud && !obj) {
      write("what are you trying to put where?");
      return;
   }

   if (loud && !obj2) {
      write("Where are you trying to put that?\n");
      return;
   }

   if (loud && !obj2->is_container()) {
      write("You can not put that there.\n");
      return;
   }

   if (obj->is_worn()) {
      if (obj->is_cursed()) {
         this_player()->targetted_action("$N $vtry to remove $o, but $vfumble.",
            nil, obj);
         write("Strange... It won't come off.\n");
         return;
      } else {
         this_player()->do_remove(obj);
         this_player()->targetted_action(obj->query_remove_message(), nil, obj);
      }
   }

   if (obj->is_wielded()) {
      if (obj->is_cursed()) {
         this_player()->targetted_action("$N $vtry to unwield $o, " +
            "but $vfumble.", nil, obj);
         write("Strange... You can't unwield that..\n");
         return;
      } else {
         this_player()->do_unwield(obj);
         this_player()->targetted_action(obj->query_unwield_message(), 
            nil, obj);
      }
   }

   if (obj->move(obj2)) {
      this_player()->targetted_action("$N $vput $o in $o1.", nil, obj, obj2);
   } else {
      this_player()->targetted_action("$N $vtryto  put $o in $o1, but $vfail.",
         nil, obj, obj2);
   }
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
         do_put(inv[i],0);
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   do_put(obj,1);
}
