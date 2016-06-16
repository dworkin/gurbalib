#include "../domain.h"

inherit DIR + "/lib/faerie";

void setup(void) {
   ::setup();

   set_name("pixie");
   set_short("A pixie");
   set_long("A tiny little naked pixie. " +
      "She has pale creamy skin and lovely locks " +
      "of blonde hair flowing from head. Her eyes " +
      "are steel blue, but soft and easy to gaze " +
      "into. She has gorgeous gossamer wings.");
}

