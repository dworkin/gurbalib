void usage() {
   write("Usage: get [-h] [all|OBJ] [from OBJ2]\n");
   write("Allows you to pick up a given object OBJ, or to take an object " +
      "from another object.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tGet everything you can pick up.\n");
   write("Examples:\n");
   write("get sword\n");
   write("get sword from chest\n");
   write("get all\n");
   write("get all from chest\n");
   write("See also: drop, open, put, remove, wear, wield\n");
}

void do_get(object obj1, object obj2, int loud) {
   string slot;
   object worn;

   if (!obj1) {
      if (loud) {
         write("What are you trying to get?");
      }
      return;
   }

   if (obj1->is_gettable() != 1) {
      if (loud) {
         write("You can not get the " + obj1->query_id() + ".");
      }
      return;
   }

   if (!obj2) {
      if (loud) {
         write("Where are you trying to get that?\n");
      }
      return;
   }

   if (!obj2->is_container()) {
      if (loud) {
         write("You can not get things from there.\n");
      }
      return;
   }

   if (obj2->is_closed()) {
      if (loud) {
         write("It is not open.\n");
      }
      return;
   }

   if (!obj1->is_gettable()) {
      if (loud) {
         write("You can not get the " + obj1->query_id() + ".");
      }
      return;
   }

   if (obj1->move(this_player())) {
      if (obj2 == this_environment()) {
         this_player()->targetted_action("$N $vpick up $o.", nil, obj1);
      } else {
         this_player()->targetted_action("$N $vpick up $o from $o1.", nil, 
            obj1, obj2);
      }
   } else {
      if (obj2 == this_environment()) {
         this_player()->targetted_action("$N $vtry to get $o, but $vfail.",
         nil, obj1);
      } else {
         this_player()->targetted_action("$N $vtry to get $o from $o1, " +
            "but $vfail.", nil, obj1, obj2);
      }
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
   } else if (sscanf(str, "%s from %s",what,where) == 2) {
   } else if (sscanf(str, "%s %s",what,where) == 2) {
   } else {
      what = str;
   }

   if (!where || (where == "")) {
      obj = this_environment();
   } else {
      obj = this_environment()->present(lowercase(where));
   }

   if (!obj) {
      write("Where are you trying to get something from?");
      return;
   }

   if (what == "all") {
      inv = this_environment()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_get(inv[i], obj, 0);
      }
      return;
   }
write("What = " + what + ", Where = " + where + "\n");

   obj2 = obj->present(lowercase(what));
   do_get(obj2, obj, 1);
}
