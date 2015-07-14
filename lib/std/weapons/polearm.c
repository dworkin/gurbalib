inherit "/std/weapon";

void set_polearm_skill(string s) {
   if (!is_standard_weapon_skill(s)) {
      s = "medium";
   }
   set_weapon_skill("combat/sharp/" + s);
}

void setup(void) {
   set_id("polearm");
   set_adj("long");
   set_short("A polearm");
   set_long("Your standard long polearm.");
   set_gettable(1);

   set_combat_stats(1, 5, 10);

   set_wield_type("both");
   set_wield_message("$N $vgrab $p $o. Ready!");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_actions(({
      "stab", "poke", "hit"
      }));
   set_polearm_skill("medium");

   set_value(30);
   set_size(4);
   set_weight(1);
}
