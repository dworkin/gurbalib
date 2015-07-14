inherit "/std/weapon";

void set_blunt_skill(string s) {
   if (!is_standard_weapon_skill(s)) {
      s = "medium";
   }
   set_weapon_skill("combat/blunt/" + s);
}

void setup(void) {
   set_id("cudgel");
   set_short("A cudgel");
   set_long("Your standard cudgel.");
   set_gettable(1);

   set_combat_stats(1, 5, 10);

   set_wield_type("single");
   set_wield_message("$N $vgrab $p $o. Ready!");
   set_unwield_message("$N $vloosen $p $vgrip on $o, and $vput it away.");
   set_weapon_actions(({
      "club", "bash", "hammer", "crush", "crack"
      }));
   set_blunt_skill("medium");

   set_value(30);
   set_size(2);
   set_weight(1);
}
