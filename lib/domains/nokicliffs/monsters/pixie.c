#include "../domain.h"

inherit DIR + "/lib/faerie";

private void add_pixie_dust() {
   object dust;

   dust = compile_object(DIR + "/obj/pixie_dust.c");
   dust->setup();
   dust->move(this_object());
}

void setup(void) {
   set_name("pixie");
   set_short("A pixie");
   set_long("A tiny little naked pixie. " +
      "She has pale creamy skin and lovely locks " +
      "of blonde hair flowing from head. Her eyes " +
      "are steel blue, but soft and easy to gaze " +
      "into. She has gorgeous gossamer wings.");
   add_pixie_dust();
}

