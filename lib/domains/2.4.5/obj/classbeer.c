#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("beer");
   set_adj("classy");
   set_short("A first class beer");
   set_long("A bottle of beer.");
   set_eatable(1);
   set_gettable(1);
   set_value(12);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = random(5) + 1;
   write("That feels good.");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + 
      " drinks a nice beer.\n");
   this_player()->increase_hp(x);
   this_object()->destruct();
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The mug breaks as it hits the ground.");
   this_object()->destruct();
}

