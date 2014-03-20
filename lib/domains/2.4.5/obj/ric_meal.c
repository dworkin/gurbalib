#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("meal");
   set_adj("rich man's");
   set_short("Rich Man's Meal");
   set_long("A lovely sausage with some cheese and wine.  " +
      "You mouth waters just looking at it.");
   set_eatable(1);
   set_gettable(1);
   set_value(90);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = random(25) + 1;
   write("That hit the spot.");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " enjoys an expensive meal.");
   this_player()->increase_hp(x);
   this_object()->destruct();
}
