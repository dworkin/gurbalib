#include "../../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("diamond");
   set_short("A diamond");
   set_long("This diamond is much larger than others you have seen in the world. " +
      "You cannot estimate the number of carats on this rock, but what you " +
      "do know about gems hints that this diamond may be worth a lot. ");
   set_value(500 + random(200));
   set_weight(1);
   set_gettable(1);
}
