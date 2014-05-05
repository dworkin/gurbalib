#include "../domain.h"

inherit DIR + "/lib/helmet";

void setup(void) {
	::setup();
   set_adj("small", "round");
   set_short("A small rusty helmet");
   set_long("A small rusty helmet, it looks like it has seen better days.  " +
      "You would have to be really desperate to put this thing on.");
}
