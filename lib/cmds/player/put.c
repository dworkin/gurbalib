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

   if (loud && !obj1) {
      write("What are you trying to put where?");
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

   if (loud && obj2->is_closed()) {
      write("It is not open.\n");
      return;
   }

   if (loud && (obj2 == this_player())) {
      write("You can not put things in your inventory, use get instead.\n");
      return;
   }

   if (obj1->is_worn()) {
      if (obj1->is_cursed()) {
         this_player()->targetted_action("$N $vtry to remove $o, but $vfumble.",
            nil, obj1);
         write("Strange... It won't come off.\n");
         return;
      } else {
         this_player()->do_remove(obj1);
         this_player()->targetted_action(obj1->query_remove_message(), 
            nil, obj1);
      }
   }

   if (obj1->is_wielded()) {
      if (obj1->is_cursed()) {
         this_player()->targetted_action("$N $vtry to unwield $o, " +
            "but $vfumble.", nil, obj1);
         write("Strange... You can't unwield that..\n");
         return;
      } else {
         this_player()->do_unwield(obj1);
         this_player()->targetted_action(obj1->query_unwield_message(), 
            nil, obj1);
      }
   }

   if (obj1->move(obj2)) {
      this_player()->targetted_action("$N $vput $o in $o1.", nil, obj1, obj2);
   } else {
      this_player()->targetted_action("$N $vtryto put $o in $o1, but $vfail.",
         nil, obj1, obj2);
   }
}

void main(string str) {
   object obj, obj2;
   object *inv;
   int i, max;
   string what, where;

   if (!str || str == "") {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (sscanf(str, "%s in %s",what,where) == 2) {
   } else if (sscanf(str, "%s at %s",what,where) == 2) {
   } else if (sscanf(str, "%s %s",what,where) == 2) {
   } else {
      write("You want to put what where?");
      return;
   }

   obj = this_player()->present(lowercase(where));
   if (!obj) {
      obj = this_player()->query_environment()->present(lowercase(where));
   }
   if (!obj) {
      write("Where are you trying to put that?");
      return;
   }

   if (what == "all") {
      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_put(inv[i], obj, 0);
      }
      return;
   }

   obj2 = this_player()->present(lowercase(what));
   if (!obj2) {
      obj2 = this_player()->query_environment()->present(lowercase(what));
   }
   do_put(obj2, obj, 1);
}
