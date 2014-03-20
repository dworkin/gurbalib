#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("sweetroll");
   add_id("roll");
   add_id("sweet roll");
   set_adj("sweet");
   set_short("A very sweet, sweetroll");
   set_long("This thing looks delicious.");
   set_eatable(1);
   set_gettable(1);
   set_value(15);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = random(5) + 1;
   write("That is heavenly.");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + 
      " eats their sweetroll.\n");
   this_player()->increase_hp(x);
   this_object()->destruct();
}

