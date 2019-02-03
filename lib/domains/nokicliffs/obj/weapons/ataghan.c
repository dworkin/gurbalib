#include "../../domain.h"

inherit DIR + "/lib/sword";

void setup(void) {
   ::setup();
   set_id("ataghan");
   set_short("An ataghan");
   set_long("An ataghan. It is an exotic sword indeed.");
}
