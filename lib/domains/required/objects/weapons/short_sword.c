inherit WEAPON;

void setup(void) {
   set_id("sword");
   set_adj("short");
   set_long("Your standard small sword.");
   set_in_room_desc("A short sword.");
   set_gettable(1);

   set_min_damage(1);
   set_max_damage(3);
   set_hit_bonus(0);

   set_weapon_skill("combat/sharp/small");

   set_wield_type("single");
   set_wield_message("$N $vwield $p $o");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_action("slash");
   set_value(1);
   set_size(10);
}
