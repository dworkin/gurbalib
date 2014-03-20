#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("special");
   set_short("Special of the house");
   set_long("The house special, its a fine drink.");
   set_eatable(1);
   set_gettable(1);
   set_value(20);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = 10;
   write("A tingling feeling goes through your body.");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " slams down a house special.\n");
   this_player()->increase_hp(x);
   this_object()->destruct();
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The mug breaks as it hits the ground.");
   this_object()->destruct();
}
