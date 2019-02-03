#include "../../domain.h"

inherit DIR + "/lib/sword";

private string format_stats_of_weapon(void) {
   return "Max: " + query_max_damage() + ", hit: +" + query_hit_bonus();
}

string query_short(void) {
   string str;
   str = ::query_short();
   str += " [" + format_stats_of_weapon() + "]";
   return str;
}

string query_long(void) {
   string str;
   str = ::query_long();
   str += "\n" + format_stats_of_weapon() + ".";
   return str;
}

void setup(void) {
   ::setup();
   set_id("falchion", "avenging falchion", "avenger");
   set_adj("avenging");
   set_short("An avenging falchion of the immortals");
   set_long("A powerful avenging falchion. " +
      "It is said that only immortals may harness its " +
      "power. The blade is shiny silver with rippling " +
      "magicks coursing the length of it casting various " +
      "hues across the blade, the meanings of which are " +
      "known only to the immortals and the ancients who " +
      "crafted these rare blades.");
   set_combat_stats(1, 300, 10);
   add_action("adjust_max_damage_cmd", "md");
   add_action("adjust_hit_bonus_cmd", "hb");
   add_action("consider_cmd", "consider");
   add_action("bump_hit_points_cmd", "maxhp");
   set_materials(({"silver"}));
   add_bane("holy");
}

int bump_hit_points_cmd(string str) {
   this_player()->set_max_hp(1000);
   write("Your max hit points have been increased. You might want " +
      "to heal yourself.");
   return 1;
}

int consider_cmd(string str) {
   object target;
   int i, sz;
   string *skills;
   string skill_detail;

   if (empty_str(str)) {
      write("Consider who, master?");
      return 1;
   }

   target = this_player()->query_environment()->present(lowercase(str));
   if (!target) {
      write(str + " does not appear to be present, master.");
      return 1;
   }

   skills = target->query_skills();
   skill_detail = "\t" + target->query_hit_skill() + "\n";
   for (i = 0, sz = sizeof(skills); i < sz; i++) {
      skill_detail += "\t" + skills[i] + ": " +
            target->query_skill(skills[i]) + "\n";
   }
   write("Master, I consider " + str + " thus: " + target->query_hp() +
      " hit points and " + target->query_mana() + " mana.");
   write("\tstatus: " + target->query_status() + "\n");
   write("\tlevel: " + target->query_level() + "\n");
   write("\tstr: " + target->query_stat("str") + ", dex: " + target->query_stat("dex") + "\n");
   write(skill_detail);

   return 1;
}

int adjust_hit_bonus_cmd(string arg) {
   int i;

   if (empty_str(arg)) {
      write("Must supply an argument, master.");
      return 1;
   }
   sscanf(arg, "%d", i);
   set_hit_bonus(i);
   write("Master, my hit bonus has been adjusted thus: " + i + ".");
   return 1;
}

int adjust_max_damage_cmd(string arg) {
   int i;

   if (empty_str(arg)) {
       write("Must supply an argument, master.");
       return 1;
   }
   sscanf(arg, "%d", i);
   set_max_damage(i);
   write("Master, my max damage has been adjusted thus: " + i + ".");
   return 1;
}

int wield_hook(object player) {
   if (query_mortal(player)) {
      player->write("You are not allowed to wield the avenging sword.\n");
   }
   return !query_mortal(player);
}

void after_wield(object player) {
   player->write("Your avenger says: " +
      "So good to see you again, master, let us " +
      "spread our vengeance across the realms!");
}

void after_unwield(object player, string cmd) {
   if (!player) {
      return;
   }
   player->write("Your avenger says: " +
      "Master, I await our next chance to spread our " +
      "vengeance across the realms!");
}
