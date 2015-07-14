#include "../domain.h"

inherit "/std/armor";
inherit "/std/modules/m_readable";

string get_color(void) {

   switch(random(5)) {
      case 0:
         return "red";
      case 1:
         return "blue";
      case 2:
         return "white";
      case 3:
         return "black";
      default:
         return "orange";
   }
}

int set_color(string str) {
   if (!str || str == "") {
      str = get_color();
   }

   set_adj(str);
   set_short("A " + str + " bandana");
   set_long("This " + str + " bandana, looks pretty stylish.  It has " +
      "a small label attached to it.");
}

void setup(void) {
   set_id("bandana", "scarf", "label");
   set_color("");

   set_gettable(1);
   set_slot("apparel");
   set_wear_message("$N $vput $o on.");
   set_remove_message("$N $vtake off $o.");

   add_action("do_shakeit", "shake");

   set_message("The label on the bandana reads: Hand wash only.\n" +
      "Shake vigorously to dry.");
   set_weight(3);
   set_size(6);
   set_value(5);
}

int do_shakeit(string str) {
   if (str == "scarf" || str == "bandana") {
      write("You vigorously shake the bandana.");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " vigorously shakes a colorful " +
         "bandana.\n");
      write("The bandana shifts it's color.");

      set_color("");
      return 1;
   }
   return 0;
}
