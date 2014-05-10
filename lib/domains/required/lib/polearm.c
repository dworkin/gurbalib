inherit "/std/weapon";

void setup(void) {
   set_id("polearm");
   set_adj("long");
   set_short("A long sword");
   set_long("Your standard long polearm.");
   set_gettable(1);

	set_combat_stats(1, 5, 10);

	set_wield_type("both");
   set_wield_message("$N $vgrab $p $o. Ready!");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_actions(({
		"stab", "poke", "hit"
	}));
   set_weapon_skill("combat/sharp/medium");

   set_value(30);
   set_size(10);
   set_weight(8);
}
