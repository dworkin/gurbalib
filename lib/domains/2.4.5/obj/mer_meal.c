#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("meal");
   set_adj("merchant's");
   set_short("Merchant's meal");
   set_long("A small bowl of stew or something, it doesn't look very tasty.");
   set_eatable(1);
   set_gettable(1);
   set_value(50);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = random(15) + 1;
   write("You eat the merchant meal.  It's not the greatest but it fills " +
      "your belly.\n");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " eats a healthy meal.\n");
   this_player()->increase_hp(x);
   this_object()->destruct();
}
