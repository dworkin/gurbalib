inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: remove [-h] [all|OBJ]" });
   lines += ({ "" });
   lines += ({ "Allows you to remove a given object OBJ, that you are " +
      "currently wearing or wielding." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tRemove everything you are wearing and wielding." });
   lines += ({ "Examples:" });
   lines += ({ "\tremove helmet" });
   lines += ({ "\tremove all" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "get");
   add_also("player", "drop");
   add_also("player", "put");
   add_also("player", "wear");
   add_also("player", "wield");
}

static void do_remove(object obj, int loud) {
   string slot;
   object worn;
   int wielded;

   if (!obj) {
      if (loud) {
         write("what are you trying to remove?");
      }
      return;
   }

   if (obj->is_worn()) {
      if (obj->is_cursed()) {
         if (loud) {
            this_player()->targeted_action(
               "$N $vtry to remove $o, but $vfumble.", nil, obj);
            write("Strange... It won't come off.\n");
         }
         return;
      }
   } else if (obj->is_wielded()) {
      wielded = 1;
      if (obj->is_cursed()) {
         if (loud) {
            this_player()->targeted_action(
               "$N $vtry to remove $o, but $vfumble.", nil, obj);
            write("Strange... It won't come off.\n");
         }
         return;
      }
   } else {
      if (loud) {
         write("You are not wearing or wielding that.\n");
      }
      return;
   }

  if (wielded) {
      this_player()->do_unwield(obj);
      this_player()->targeted_action(obj->query_unwield_message(), nil, obj);
      obj->after_unwield(this_player(), "remove");
   } else {
      this_player()->do_remove(obj);
      this_player()->targeted_action(obj->query_remove_message(), nil, obj);
      obj->after_unwear(this_player(), "remove");
   }
}

static void main(string str) {
   object obj, *inv;
   int i, max;

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
      for (i = 0; i < max; i++) {
         do_remove(inv[i], 0);
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   do_remove(obj, 1);
}
