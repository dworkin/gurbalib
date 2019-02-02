#include "../../domain.h"

inherit DIR + "/lib/blunt";

void setup(void) {
   string *a;

   ::setup();

   set_id("mace");
   set_short("A mace");
   set_adj("");
   set_long("The is the favored weapons of clerics. This mace appears " +
      "to be used a lot, but it still is in excellent condition.");

   a = query_weapon_actions();
   a += ({ "mangle", "clobber" });
   set_weapon_actions(a);
}
