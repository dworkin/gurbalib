void usage() {
   string *lines;

   lines = ({ "Usage: drop [-h] [all|OBJ]" });
   lines += ({ "" });
   lines += ({ "Allows you to drop a given object OBJ." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tDrop everything you are carring." });
   lines += ({ "Examples:" });
   lines += ({ "\tdrop sword" });
   lines += ({ "\tdrop all" });
   lines += ({ "See also:" });
   lines += ({ "\tget, put, remove, wear, wield" });

   this_player()->more(lines);
}

void do_drop(object obj, int loud) {
   string slot;
   object worn;

   if (!obj) {
      if (loud) {
         write("what are you trying to drop?");
      }
      return;
   }

   if (obj->is_undroppable()) {
      if (loud) {
         write("You cannot drop that.");
      }
      return;
   }
   if (obj->query_worn() == 1) {
      if (obj->is_cursed()) {
         if (loud) {
            this_player()->targetted_action("$N $vtry to remove $o, " +
               "but $vfumble.", nil, obj);
            write("Strange... It won't come off.\n");
         } 
         return;
      } 
      this_player()->do_remove(obj);
      this_player()->targetted_action(obj->query_remove_message(), nil, obj);
   }
   if (obj->query_wielded() == 1) {
      if (obj->is_cursed()) {
         if (loud) {
            this_player()->targetted_action("$N $vtry to remove $o, " +
               "but $vfumble.", nil, obj);
            write("Strange... It won't come off.\n");
         } 
         return;
      }
      this_player()->do_unwield(obj);
      this_player()->targetted_action(obj->query_unwield_message(), nil, obj);
   }

   if (obj->move(this_environment())) { 
      this_player()->targetted_action("$N $vdrop $o.", nil, obj);
      obj->post_drop();
   } else {
      this_player()->targetted_action("$N $vtry to drop $o, but $vfail.", 
         nil, obj);
   }
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
         do_drop(inv[i],0);
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   do_drop(obj,1);
}
