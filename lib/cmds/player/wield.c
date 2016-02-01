inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: wield [-h] [all|obj]" });
   lines += ({ "" });
   lines += ({ "Allows you to equip a given object OBJ." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tEquip all available objects." });
   lines += ({ "Examples:" });
   lines += ({ "\twield sword" });
   lines += ({ "\twield axe" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "get");
   add_also("player", "drop");
   add_also("player", "put");
   add_also("player", "remove");
   add_also("player", "wear");
}

static int do_wield(object obj, int loud) {
   string slot;
   object *wielded;

   if (!obj) {
      if (loud) {
         write("Maybe you should get one first?");
      }
      return 0;
   }

   if (!obj->is_wieldable()) {
      if (loud) {
         write("You can't wield that.");
      }
      return 0;
   }

   if (obj->query_wielded() == 1) {
      if (loud) {
         write("You already are wielding that.");
      }
      return 0;
   }

   wielded = this_player()->query_wielded();

   if (obj->query_wield_type() == "single") {
      if (sizeof(wielded) >= 2) {
         write("Your hands are full.");
         return 0;
      }
   } else {
      if (sizeof(wielded) != 0) {
         write("You are already wielding something else.");
         return 0;
      }
   }

   this_player()->do_wield(obj);
   this_player()->targeted_action(obj->query_wield_message(), nil, obj);
      obj->after_wield(this_player());
   return 1;
}

static void main(string str) {
   object obj, *inv;
   int i, max, done;

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

   if (str == "all") {
      inv = this_player()->query_inventory();

      max = sizeof(inv);
      done = 0;

      for (i = 0; i < max; i++) {
         if (inv[i]->wield_hook(this_player())) {
            if (do_wield(inv[i], 0)) {
               done = 1;
            }
         }
      }

      if (!done) {
         write("You have nothing to wield.\n");
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      write("Wield what?");
      return;
   }
   if (obj->wield_hook(this_player())) {
      do_wield(obj, 1);
   }
}
