#include "../../domain.h"

inherit DIR + "/lib/armor";

void setup(void) {
   set_id("chain mail");
   add_ids("mail");
   set_short("A set of chain mail armor");
   set_long("This set of chain mail has a few dings and dents. " +
      "Nevertheless, it is still in a condition that makes it " +
      "suitable for most adventurers.");
   set_medium();
}
