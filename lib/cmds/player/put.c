inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: put [-h] [all|OBJ] [at|in] OBJ2" });
   lines += ({ "" });
   lines += ({ "Allows you to put OBJ inside OBJ2" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tPut everything you are carrying in OBJ2." });
   lines += ({ "Examples:" });
   lines += ({ "\tput sword in chest" });
   lines += ({ "\tput all in chest" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "get");
   add_also("player", "drop");
   add_also("player", "remove");
   add_also("player", "wear");
   add_also("player", "wield");
}

static void do_put(object obj1, object obj2, int loud) {
   string slot;
   object worn;

   if (!obj1) {
      if (loud) {
         write("What are you trying to put where?");
      }
      return;
   }

   if (!obj2) {
      if (loud) {
         write("Where are you trying to put that?\n");
      }
      return;
   }

   if (!obj2->is_container()) {
      if (loud) {
         write("You can not put that there.\n");
      }
      return;
   }

   if (obj2->is_closed()) {
      if (loud) {
         write("It is not open.\n");
      }
      return;
   }

   if (obj2 == this_player()) {
      if (loud) {
         write("You can not put things in your inventory, use get instead.\n");
      }
      return;
   }

   if (obj1->is_worn()) {
      if (obj1->is_cursed()) {
         this_player()->targeted_action("$N $vtry to remove $o, but $vfumble.",
            nil, obj1);
         write("Strange... It won't come off.\n");
         return;
      } else {
         this_player()->do_remove(obj1);
         this_player()->targeted_action(obj1->query_remove_message(), 
            nil, obj1);
      }
   }

   if (obj1->is_wielded()) {
      if (obj1->is_cursed()) {
         this_player()->targeted_action("$N $vtry to unwield $o, " +
            "but $vfumble.", nil, obj1);
         write("Strange... You can't unwield that..\n");
         return;
      } else {
         this_player()->do_unwield(obj1);
         this_player()->targeted_action(obj1->query_unwield_message(), 
            nil, obj1);
      }
   }

   if (!obj1->can_move(obj2)) {
      this_player()->targeted_action("$N $vtry to put $o in $o1 but $n $vfail.",
            nil, obj1, obj2);
      return;
   }

   if (obj1->move(obj2)) {
      this_player()->targeted_action("$N $vput $o in $o1.", nil, obj1, obj2);
      obj2->after_move(this_player(), obj1);
   } else {
      this_player()->targeted_action("$N $vtry to put $o in $o1, but it " +
         "does not fit.", nil, obj1, obj2);
   }
}

static void main(string str) {
   object obj, obj2;
   object *inv;
   int i, max;
   string what, where;

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
   } else if (sscanf(str, "%s at %s", what, where) == 2) {
   } else if (sscanf(str, "%s %s", what, where) == 2) {
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
      if (obj->is_closed()) {
         write("It is not open.\n");
         return;
      }

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
