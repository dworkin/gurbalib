#include "../../domain.h"

inherit DIR + "/lib/laughing_horse_inn_drink";

void setup(void) {
   set_id("mixture");
   add_ids("doctor's special mixture", "special mixture", "special");
   set_short("Doctor's special mixture");
   set_long("The drink comes in a strange special crystalline goblet. " +
      "The drink itself is a swirling rainbow colored liquid.");
   set_eatable(1);
   set_gettable(1);
   set_value(150);
}

int do_eat(void) {
   this_player()->simple_action("$N $vdrink the special mixture and " +
      "$p guts catch fire.");
   this_player()->increase_hp(12 + random(2));
   this_object()->destruct();

   return 1;
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The crystalline goblet shoots a small rainbow into the " +
      "sky and you think you hear a xylophone at the same time.");
   this_object()->destruct();
}
