#include "../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("jacket");
   set_adj("leather", "black");
   set_short("A worn but sturdy leather jacket");
   set_long("This is the kind of leather jacket all %^RED%^bad%^RESET%^ " +
      "dudes wear.  On the back is a lot of rivets making the " +
      "pattern of a star.");
   set_gettable(1);
   set_slot("body");
   set_wear_message("$N $vput on $o. Man, $N $vare cool!");
   set_remove_message("$N $vtake off $o, and suddenly $vlook extremely dull.");
   set_ac(3);
   set_value(50);
   set_size(3);
   set_weight(5);
}
