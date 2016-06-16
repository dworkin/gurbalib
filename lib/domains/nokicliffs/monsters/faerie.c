#include "../domain.h"

inherit DIR + "/lib/faerie";

void setup(void) {
   ::setup();

   set_name("faerie");
   set_short("A faerie");
   set_long("A tiny little naked faerie. " +
      "Her creamy skin almost glows in the " +
      "sunlight of the oak grove. Her sandy " +
      "blonde hair flows like a heavenly " +
      "waterfall over her bare shoulders. " +
      "She has gorgeous gossamer wings.");
}

