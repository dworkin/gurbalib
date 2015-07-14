inherit "/std/weapon";

void set_sword_skill(string s) {
   if (!is_standard_weapon_skill(s)) {
      s = "medium";
   }
   set_weapon_skill("combat/edge/" + s);
}

void setup(void) {
   set_id("sword");
   set_adj("long");
   set_short("A long sword");
   set_long("Your standard long sword.");
   set_gettable(1);

   set_combat_stats(1, 5, 10);

   set_wield_type("single");
   set_wield_message("$N $vgrab $p $o. Ready!");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_actions(({
      "slash", "slice", "dice", "cut", "gash", "stab", "poke", "gouge"
      }));
   set_sword_skill("medium");

   set_value(30);
   set_size(2);
   set_weight(2);
}
