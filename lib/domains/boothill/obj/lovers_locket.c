#include "../domain.h"

inherit "/std/armor";
inherit "/std/modules/m_readable";

int broken;
object twin;

void setup(void) {
   set_id("lovers locket");

   add_id("locket");
   set_gettable(1);
   set_slot("apparel");
   set_wear_message("$N $vput $o on.");
   set_remove_message("$N $vtake off $o.");

   set_short("A lovers locket.");
   set_long("A golden heart shaped locket, engraved with the word LOVE!  " +
      "There appears to be some writing on the back that you can read.");
   broken = 0;

   add_object_command("break","do_breakit");
   add_object_command("squeeze","do_squeezeit");

   set_message("Think of your love, squeeze the locket and you'll be with " +
      "them.");
   set_weight(3);
   set_value(5);
}

do_half(object obj) {
   setup();
   broken = 1;
   set_short("Half a locket.");
   set_long("Half of a golden heart shaped locket, engraved with the word " +
      "\"VE\"!  There appears to be some writing on the back that you can " +
      "read.");
   twin = obj;
}

int do_breakit(string str) {
   if (str == "lovers locket" || str == "locket") {
      if (broken == 1) {
         write("This locket is already broken.\n");
      } else { 
         object obj;

         write("You snap the locket into two pieces.");
         this_player()->query_environment()->tell_room(this_player(),
            this_player()->query_Name() + " breaks their locket into two " +
            "pieces.\n");
         broken = 1;
         set_short("Half a locket.");
         set_long("Half of a golden heart shaped locket, engraved with the " +
            "word \"LO\"!  There appears to be some writing on the back " +
            "that you can read.");

         obj = clone_object(DIR + "/obj/lovers_locket.c");
         twin = obj;
         obj->do_half(this_object());
         obj->move(this_object()->query_enviornment());

      }
      return 1;
   }
   return 0;
}

int do_squeezeit(string str) {
   if (str == "locket" || str == "lovers locket") {
      write("You squeeze the locket and dream of your lover.\n");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " squeezes their locket and pauses " +
         "for a moment.");
      if (find_object(twin)) {
         /* XXX Need to fix movement first...
         this_player()->magic_move(twin->query_environment()); */
      } else {
         write("You miss them.\n");
      }
      return 1;
   }
   return 0;
}
