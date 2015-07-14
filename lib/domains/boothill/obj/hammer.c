#include "../domain.h"

inherit "/std/weapon";

void setup(void) {
   set_id("hammer");
   set_adj("small");
   set_short("A small hammer");
   set_long("A sturdy hammer.  It looks quite small for combat, but it will " +
      "allow you to hang a picture in a pinch.");
   set_gettable(1);

   set_min_damage(1);
   set_max_damage(1);
   set_hit_bonus(0);

   set_weapon_skill("combat/blunt/small");

   set_wield_type("single");
   set_wield_message("$N $vwield $p $o.");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_action("bash");
   set_value(20);
   set_size(1);
   set_weight(6);
}
