inherit OBJECT;
string tied_to;
object tied_to_obj;

void setup(void) {
   set_id("stethoscope");
   set_adj("old");
   set_in_room_desc("A stethoscope");
   set_long("An old stethoscope.");
   set_gettable(1);

   set_value(15);
   set_weight(1);
// XXX add action "listen";
// XXX add action "apply";
}

int listen(string str) {
   write("You must apply stethoscope to something.\n");
   return 1;
}

int apply(string str) {
   object obj;

   if (!str) 
      return 0;

   if (query_environment() != this_player()) {
      write("You must have the stethoscope on you to use it.\n");
      return 1;
   }
   obj = this_player()->query_environment()->present(str);
   if (!obj) {
      if (sscanf(str, "stethoscope to %s", what) != 1) {
         write("On what?\n");
         return 1;
      }
      obj = this_player()->query_environment()->present(str);
      if (!obj) {
         write("On what?\n");
         return 1;
      }
   }

   write("You listen to the " + obj->query_name() + "\n");

// XXX Tell others what the player is doing...

   if (living(ob)) {
      write("Thub Whub\n");
   } else {
      write("You hear nothing.\n");
   }
   return 1;
}
