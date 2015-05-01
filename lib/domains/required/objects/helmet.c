#include "../domain.h"

inherit "/std/armor";

void setup(void) {
   set_adj("small", "round");
   set_short("A small rusty helmet");
   set_long("A small rusty helmet, it looks like it has seen better days.  " +
      "You would have to be really desperate to put this thing on.");
}
