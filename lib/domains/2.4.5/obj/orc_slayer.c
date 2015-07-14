#include "../domain.h"

inherit "/std/weapon";

void setup(void) {
   set_id("orc slayer");
   add_id("sword");
   add_id("short sword");
   set_short("Short sword");
   set_long("This is a very fine blade.  It is covered with ancient runes." +
      "  Engraved on it is a picture of the sword slicing an orc in half.");
   set_gettable(1);

   set_min_damage(5);
   set_max_damage(10);
   set_hit_bonus(2);

   set_weapon_skill("combat/sharp/small");

   set_wield_type("single");
   set_wield_message("$N $vwield $p $o.");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_action("slash");
   set_value(200);
   set_size(2);
   set_weight(10);
}
