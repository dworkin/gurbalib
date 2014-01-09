#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("firebreather");
   set_short("A firebreather");
   set_long("This is an assume drink.");
   set_eatable(1);
   set_gettable(1);
   set_value(2);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = random(2) + 1;
   write("A shock wave runs through your body.");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + 
      " gulps down a flaming brew that looks wicked.\n");
   this_player()->increase_hp(x);
   this_object()->destruct();
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The mug breaks as it hits the ground.");
   this_object()->destruct();
}

