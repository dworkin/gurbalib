void usage() {
   string *lines;

   lines = ({ "Usage: wear [-h] [all|OBJ]" });
   lines += ({ "" });
   lines += ({ "Allows you to wear a given object OBJ." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tWear all available objects." });
   lines += ({ "Examples:" });
   lines += ({ "\twear helmet" });
   lines += ({ "\twear pants" });
   lines += ({ "See also:" });
   lines += ({ "\tget, drop, put, remove, wield" });

   this_player()->more(lines);
}

void do_wear(object obj, int loud) {
   string slot;
   object worn;

   if (!obj) {
      if (loud) {
         write("what are you trying to wear?");
      }
      return;
   }

   if (!obj->is_wearable()) {
      if (loud) {
         write("You cannot wear that.");
      }
      return;
   }
   if (obj->query_worn() == 1) {
      if (loud) {
         write("You're already wearing the " + obj->query_id() + ".");
      }
      return;
   }

   slot = obj->query_slot();
   if (!obj->query_valid_slot(slot)) {
      if (loud) {
         write("You do not have a place to wear that.\n");
      }
      return;
   }

   worn = this_player()->query_slot(slot);
   if (worn && (slot != "apparel")) {
      if (loud) {
         write("You are already wearing a " + worn->query_id() + ".");
         return;
      }
   }

   this_player()->do_wear(obj);
   this_player()->targetted_action(obj->query_wear_message(), nil, obj);
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
         do_wear(inv[i],0);
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   do_wear(obj,1);
}
