#include "../../domain.h"

inherit "/std/weapons/blunt";

void setup(void) {
   set_id("whip");
   set_adj("leather");
   set_short("A leather whip");
   set_long("A long leather whip turned black by all the dried blood.");

   set_weapon_actions(({ "crack", "whip" }));
}
