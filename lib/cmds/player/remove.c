inherit M_COMMAND;

void usage() {
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
   lines += ({ "See also:" });
   lines += ({ "\tget, drop, put, wear, wield" });

   this_player()->more(lines);
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

   this_player()->do_remove(obj);
   if (wielded) {
      this_player()->targeted_action(obj->query_unwield_message(), nil, obj);
   } else {
      this_player()->targeted_action(obj->query_remove_message(), nil, obj);
   }
}

static void main(string str) {
   object obj;
   object *inv;
   int i, max;

   if (empty_str(str)) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
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
         do_remove(inv[i],0);
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   do_remove(obj,1);
}
