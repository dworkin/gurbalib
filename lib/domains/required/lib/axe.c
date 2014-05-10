inherit "/std/weapon";

void setup(void) {
   set_id("axe");
   set_adj("battle");
   set_short("A battle axe");
   set_long("Your standard battle axe.");
   set_gettable(1);

	set_combat_stats(1, 5, 10);

   set_wield_type("single");
   set_wield_message("$N $vgrab $p $o. Ready!");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_actions(({
		"slash", "slice", "gash", "gouge"
	}));
   set_weapon_skill("combat/edge/medium");

   set_value(30);
   set_size(10);
   set_weight(8);
}

