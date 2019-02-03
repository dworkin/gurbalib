#include "../../domain.h"

inherit DIR + "/lib/laughing_horse_inn_drink";

void setup(void) {
   set_id("whiskey");
   add_ids("whiskey on the rocks");
   set_short("A whiskey on the rocks");
   set_long("A small glass of whiskey on the rocks.");
   set_eatable(1);
   set_gettable(1);
   set_value(50);
}

int do_eat(void) {
   this_player()->simple_action("$N $vdrink whiskey on the rocks " +
      "then steam $vcome out of $p ears.");
   this_player()->increase_hp(12 + random(2));
   this_object()->destruct();

   return 1;
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The shot glass shatters as it hits the ground.");
   this_object()->destruct();
}
