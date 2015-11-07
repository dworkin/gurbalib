inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: look [-h] [[at|in] OBJ]" });
   lines += ({ " " });
   lines += ({ "Allows you to get more details on a given object OBJ." });
   lines += ({ "If no argument is given look at your surroundings." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlook" });
   lines += ({ "\tlook at tree" });
   lines += ({ "\tlook in chest" });
   lines += ({ "See also:" });

   lines += ({ "\tbuy, extinguish, identify, light, list, listen, " +
      "search, sell, value" });

   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who" 
         });
   }

   return lines;
}

static void do_look_liv(object obj) {
   int i, flag;
   object *objs;

   this_environment()->tell_room(this_player(), this_player()->query_Name() +
      " looks at " + capitalize(obj->query_id()) + ".\n");

   write("%^PLAYER%^" + obj->query_short() + "%^RESET%^\n");

   write(obj->query_long());
   write("A " + obj->query_gender() + " " + obj->query_race() +
      " who is " + obj->query_status() + "\n");

   flag = 0;
   objs = obj->query_inventory();

   if (obj->query_gender() == "male") {
      write(" \nHe is using:\n");
   } else if (obj->query_gender() == "female") {
      write(" \nShe is using:\n");
   } else {
      write(" \nIt is using:\n");
   }

   for (i = 0; i < sizeof(objs); i++) {
      if (objs[i]->is_worn()) {
         write("  " + objs[i]->query_short() + " %^CYAN%^[" +
            objs[i]->query_wear_position() + "]%^RESET%^\n");
         flag = 1;
      } else if (objs[i]->is_wielded()) {
         write("  " + objs[i]->query_short() + " %^CYAN%^[" +
            objs[i]->query_wield_position() + "]%^RESET%^\n");
         flag = 1;
      }
   }
   if (flag == 0) {
      write("  Nothing.");
   }
}

static void main(string str) {
   string what;
   object obj;

   if (empty_str(str)) {
      obj = this_environment();
   } else {

      if (sscanf(str, "-%s", str)) {
         this_player()->more(usage());
         return;
      }

      if (sscanf(str, "in %s", what) == 1) {
      } else if (sscanf(str, "at %s", what) == 1) {
      } else {
         what = str;
      }

      if (member_array(what, this_environment()->query_items() ) > -1) {
         this_environment()->tell_room(this_player(), 
            this_player()->query_Name( ) + " looks at the " + 
            lowercase(what) + ".\n");
         write(this_environment()->query_item(what));
         return;
      }

      obj = this_player()->present(lowercase(what));
      if (!obj) {
         obj = this_environment()->present(lowercase(what));
      }
   } 

   if (!obj) {
      write("Look at what?");
      return;
   }

   this_player()->do_look(obj);
}
