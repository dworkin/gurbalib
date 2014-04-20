#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("beer");
   add_id("mug");
   set_adj("mug of");
   set_short("A mug of beer");
   set_long("A stout mug of beer.");
   set_eatable(1);
   set_gettable(1);
   set_value(2);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = random(2) + 1;
   write("That hits the spot.");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " drinks a stout mug of beer.\n");
   this_player()->increase_hp(x);
   this_object()->destruct();
   return 1;
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The mug breaks as it hits the ground.");
   this_object()->destruct();
}
