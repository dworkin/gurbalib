#include "../domain.h"

inherit "/std/weapon";

void setup(void) {
   set_id("sword");
   set_adj("small");
   set_short("A small sword");
   set_long("Your standard small sword.");
   set_gettable(1);

   set_min_damage(1);
   set_max_damage(5);
   set_hit_bonus(10);

   set_wield_type("single");
   set_wield_message("$N $vgrab $p $o. Ready!");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_action("slash");
   set_weapon_skill("combat/sharp/small");

   set_value(30);
   set_size(1);
   set_weight(8);
}
