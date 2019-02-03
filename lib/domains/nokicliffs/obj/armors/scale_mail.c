#include "../../domain.h"

inherit DIR + "/lib/armor";

void setup(void) {
   set_id("scale mail");
   add_ids("mail");
   set_short("A set of scale mail armor");
   set_long("This set of scale mail comes already battle " +
      "tested. It is still in a condition that makes it " +
      "suitable for most adventurers.");
   set_medium();
}
