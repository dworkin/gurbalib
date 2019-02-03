#include "../../domain.h"

inherit DIR + "/lib/sword";

void setup(void) {
   ::setup();
   set_id("kris");
   set_adj("");
   set_short("A kris");
   set_long("The serrated blade of this weapon looks " +
      "like it makes nasty cuts.");
   set_sword_skill("small");
   set_weapon_actions(({
      "slash", "slice", "dice", "cut", "gash", "tear"
   }));
}
