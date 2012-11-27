void usage() {
   write("Usage: get [-h] [all|OBJ] [from OBJ2]\n");
   write("Allows you to pick up a given object OBJ, or to take an object " +
      "from another object.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tGet everything you can pick up.\n");
   write("See also: put, open, drop.\n");
}

void do_get(object obj1, object obj2, int loud) {
   string slot;
   object worn;

   if (loud && !obj1) {
      write("What are you trying to get?");
      return;
   }

   if (loud && !obj2) {
      write("Where are you trying to get that?\n");
      return;
   }

   if (loud && !obj2->is_container()) {
      write("You can not get things from there.\n");
      return;
   }

   if (loud && obj2->is_closed()) {
      write("It is not open.\n");
      return;
   }

   if (loud && (obj2 == this_player())) {
      write("You can not get things from your inventory.\n");
      return;
   }

   if (loud && !obj1->is_gettable()) {
      write("You can not get the " + obj1->query_id() + ".");
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
      obj = this_player()->query_environment();
   }

   if (!obj) {
      obj = this_player()->present(lowercase(where));
   }
   if (!obj) {
      obj = this_player()->query_environment()->present(lowercase(where));
   }
   if (!obj) {
      write("Where are you trying to get something from?");
      return;
   }

   if (what == "all") {
      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_get(inv[i], obj, 0);
      }
      return;
   }

   obj2 = this_player()->present(lowercase(what));
   if (!obj2) {
      obj2 = this_player()->query_environment()->present(lowercase(what));
   }
   do_get(obj2, obj, 1);
}
