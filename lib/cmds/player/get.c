void usage() {
   string *lines;

   lines = ({ "Usage: get [-h] [all|OBJ] [from OBJ2]" });
   lines += ({ "" });
   lines += ({ "Allows you to pick up a given object OBJ, or to take an " +
      "object from another object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tGet everything you can pick up." });
   lines += ({ "Examples:" });
   lines += ({ "\tget sword" });
   lines += ({ "\tget sword from chest" });
   lines += ({ "\tget all" });
   lines += ({ "\tget all from chest" });
   lines += ({ "See also:" });
   lines += ({ "\tdrop, open, put, remove, wear, wield" });

   this_player()->more(lines);
}

int do_get(object obj1, object obj2, int loud) {
   string slot;
   object worn;

   if (!obj1) {
      if (loud) {
         write("What are you trying to get?");
      }
      return 0;
   }

   if (obj1->is_gettable() != 1) {
      if (loud) {
         write("You can not get the " + obj1->query_id() + ".");
      }
      return 0;
   }

   if (!obj2) {
      if (loud) {
         write("Where are you trying to get that?\n");
      }
      return 0;
   }

   if (!obj2->is_container()) {
      if (loud) {
         write("You can not get things from there.\n");
      }
      return 0;
   }

   if (obj2->is_closed()) {
      if (loud) {
         write("It is not open.\n");
      }
      return 0;
   }

   if (!obj1->is_gettable()) {
      if (loud) {
         write("You can not get the " + obj1->query_id() + ".");
      }
      return 0;
   }

   if (obj1->move(this_player())) {
      if (obj2 == this_environment()) {
         this_player()->targetted_action("$N $vpick up $o.", nil, obj1);
      } else {
         this_player()->targetted_action("$N $vpick up $o from $o1.", nil, 
            obj1, obj2);
      }
      return 1;
   } else {
      if (obj2 == this_environment()) {
         this_player()->targetted_action("$N $vtry to get $o, but $vfail.",
         nil, obj1);
      } else {
         this_player()->targetted_action("$N $vtry to get $o from $o1, " +
            "but $vfail.", nil, obj1, obj2);
      }
   }
   return 0;
}

void main(string str) {
   object obj, obj2;
   object *inv;
   int i, max, done;
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
      inv = obj->query_inventory();
      max = sizeof(inv);
      done = 0;
      for (i = 0; i < max; i++) {
         if (do_get(inv[i], obj, 0)) done = 1;
      }
      if (!done) {
         write("There is nothing here to get.\n");
      }
      return;
   }

   obj2 = obj->present(lowercase(what));
   do_get(obj2, obj, 1);
}
