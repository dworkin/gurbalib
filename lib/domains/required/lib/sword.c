inherit "/std/weapon";

static nomask void set_combat_stats(int min_d, int max_d, int hb) {
	set_min_damage(min_d);
	set_max_damage(max_d);
	set_hit_bonus(hb);
}

private string valid_weapon_skill(string str) {
	if (empty_str(str) ||
	 (str != "large" && str != "medium" && str != "small")) {
		str = "small";
	}
	return str;
}

void set_weapon_skill(string str) {
	::set_weapon_skill("combat/sharp/" + valid_weapon_skill(str));
}

void setup(void) {
   set_id("sword");
   set_adj("small");
   set_short("A small sword");
   set_long("Your standard small sword.");
   set_gettable(1);

	set_combat_stats(1, 5, 10);

   set_wield_type("single");
   set_wield_message("$N $vgrab $p $o. Ready!");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_action("slash");
   set_weapon_skill("small");

   set_value(30);
   set_size(10);
   set_weight(8);
}
