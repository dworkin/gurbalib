#include "../../domain.h"

inherit DIR + "/lib/armor";

void setup(void) {
   set_id("leather");
   set_short("A suit of leather armor");
   set_long("This fine suit of leather armor looks stylish " +
      "and protects you in combat at the same time.");
   set_light();
}
