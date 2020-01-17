#include "../domain.h"

inherit "/std/object";

int do_eat(void) {
   this_player()->targeted_action("$N $veat some garlic.", nil);
   this_object()->destruct();
   return 1;
}

void setup(void) {
   set_id("garlic");
   set_short("A garlic clove");
   set_long("A garlic clove. It has a strong garlic smell coming from it.");
   set_gettable(1);
   set_value(5);
   set_weight(1);
   add_bane("garlic");
   set_eatable(1);
}

