#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("stethoscope");
   set_adj("old");
   set_short("A stethoscope");
   set_long("An old stethoscope.");
   set_gettable(1);

   set_value(15);
   set_weight(1);
   add_action("apply", "apply");
}

int do_listen(string str) {
   write("You must apply stethoscope to something.\n");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " fiddles with their stethoscope.\n");
   return 1;
}

int apply(string str) {
   object obj;
   string what;

   if (!str) {
      return 0;
   }

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
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " uses a stethoscope to listen to " +
      obj->query_name() + "\n");

   if (obj->is_living()) {
      write("Thub Whub\n");
   } else {
      write("You hear nothing.\n");
   }
   return 1;
}
