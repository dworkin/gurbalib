#include "../../domain.h"

inherit DIR + "/lib/laughing_horse_inn_drink";

void setup(void) {
   set_id("beer");
   add_ids("large beer", "mug of beer");
   set_adj("large");
   set_short("A large beer");
   set_long("A stout mug of beer.");
   set_value(12);
}

int do_eat(void) {
   this_player()->simple_action("$N $vdrink the best beer $n ever tasted.");
   this_player()->increase_hp(12 + random(2));
   this_object()->destruct();

   return 1;
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The mug breaks as it hits the ground.");
   this_object()->destruct();
}
