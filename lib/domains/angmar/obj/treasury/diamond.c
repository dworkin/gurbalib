#include "../../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("diamond");
   set_short("A diamond");
   set_long("The facets of the sapphire shimmer and glint in the light. "+
            "You examine it closely, and notice the workmanship inherent in the gem. "+
            "This is a fine stone, indeed.");
   set_value(500 + random(150));
   set_weight(1);
   set_gettable(1);
}
