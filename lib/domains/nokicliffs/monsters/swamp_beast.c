#include "../domain.h"

inherit DIR + "/lib/monster";

void setup(void) {
   set_name("swamp beast");
   add_id("beast");
   set_short("A swamp beast");
   set_long("It has a tangle a mangrove roots wrapped around " +
      "what can only be described as a very deadly cypress tree.");
}
