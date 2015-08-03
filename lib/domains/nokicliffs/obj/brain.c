#include "../domain.h"

inherit obj "/std/object";

void setup(void) {
   set_id("brain");
   add_adj("mystic");
   add_id("mystic brain");
   set_short("A mystic brain of unknown origins");
   set_long("A mystic brain of unknown origins. It probably isn't of this " +
      "world. It is also most likely imbued with some strange magic. You " +
      "might consider not holding on to it longer than is absolutely " +
      "necessary. There certainly are others who have uses for such things."); 
   set_gettable(1);
   set_weight(1);
   set_value(0);
}

