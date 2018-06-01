inherit M_COMMAND;
inherit "/std/modules/m_messages";

string *usage(void) {
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
   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "drop");
   add_also("player", "open");
   add_also("player", "put");
   add_also("player", "remove");
   add_also("player", "wear");
   add_also("player", "wield");
}

static int get_coins(object here, int amount, string type) {
   object obj;
   string str;
   int value;

   obj = here->present("coin");
   value = obj->query_value();
   if (amount > value) {
      write("There are not that many coins here.\n");
   } else {
      type = obj->query_currency();
      str = "$N $vpick up " + amount + " " + type +
          + "s.";
      this_player()->targeted_action(str, this_player());

      if (amount == value) {
         destruct_object(obj);
      } else {
         obj->set_value(value - amount);
      }
      this_player()->add_money(type, amount);
   }

   return 1;
}

static int do_get(object obj1, object obj2, int loud) {
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
   if (obj2->is_living()) {
      if (loud) {
         write("Why don't you try asking for that.\n");
      }
      return 0;
   }

   if (obj2->is_closed()) {
      if (loud) {
         write("It is not open.\n");
      }
      return 0;
   }

   if (obj1->is_money()) {
      int x;

      x = obj1->query_value();
      get_coins(obj1->query_environment(), x, obj1->query_currency());
      return 1;
   }

   if (!this_player()->can_carry(obj1)) {
      this_player()->message("Your inventory is full so you " +
         "cannot carry the " + obj1->query_id() + ".");
      return 1;
   }

   if (obj1->move(this_player())) {
      if (obj2 == this_environment()) {
         this_player()->targeted_action("$N $vpick up $o.", nil, obj1);
      } else {
         this_player()->targeted_action("$N $vpick up $o from $t.", obj2, 
            obj1);
      }
      return 1;
   } else {
      if (obj2 == this_environment()) {
         this_player()->targeted_action("$N $vtry to get $o, but $vfail.",
         nil, obj1);
      } else {
         this_player()->targeted_action("$N $vtry to get $o from $t, " +
            "but $vfail.", obj2, obj1);
      }
   }
   return 0;
}

static void main(string str) {
   object obj, obj2, *inv;
   int i, max, done, amount;
   string what, where, type;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   if (sscanf(str, "%s in %s", what, where) == 2) {
   } else if (sscanf(str, "%s from %s", what, where) == 2) {
   } else if (sscanf(str, "%s %d", what, amount) == 2) {
      what = str;
   } else if (sscanf(str, "%s %s", what, where) == 2) {
   } else if (sscanf(str, "%d %s", amount, type) == 2) {
      if (get_coins(this_environment(), amount, type)) {
         return;
      } else {
         what = str;
      }
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
      if (obj->is_closed()) {
         write("It is not open.\n");
         return;
      }  

      inv = obj->query_inventory();
      max = sizeof(inv);
      done = 0;

      for (i = 0; i < max; i++) {
         if (do_get(inv[i], obj, 0)) {
            done = 1;
         }
      }
      if (!done) {
         write("There is nothing here to get.\n");
      }
      return;
   }

   obj2 = obj->present(lowercase(what));
   do_get(obj2, obj, 1);
}
