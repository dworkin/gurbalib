#include "../domain.h"

inherit "/std/weapon";

void setup(void) {
   set_id("knife");
   set_short("A curved knife");
   set_long("A small sharp knife with a curved blade.");
   set_gettable(1);

   set_min_damage(1);
   set_max_damage(3);
   set_hit_bonus(0);

   set_weapon_skill("combat/sharp/small");

   set_wield_type("single");
   set_wield_message("$N $vwield $p $o.");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_action("slash");
   set_value(8);
   set_size(1);
   set_weight(2);
}
