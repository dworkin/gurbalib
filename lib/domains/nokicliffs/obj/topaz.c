#include "../domain.h"

inherit "/std/object";
inherit NOKICLIFFS_LIGHT_EFFECT_LIB;

void setup(void) {
   set_id("topaz");
   set_short("A topaz");
   set_long("A topaz, cut and polished by a gem master.");
   set_gettable(1);
   set_value(random(200) + 200);
   set_weight(1);
}
