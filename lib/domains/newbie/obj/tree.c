#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("tree");
   set_short("A large dead tree");
   set_long("A large dead tree.  This thing looks ancient.  " +
      "You might be able to break off a branch and use it as a weapon.");
}
