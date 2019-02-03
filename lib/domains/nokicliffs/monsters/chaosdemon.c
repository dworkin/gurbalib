#include "../domain.h"

inherit "/std/monster";

void monster_died(void) {
   object shard;

   if (nilp(killer) || killer->is_quest_completed(NOKICLIFFS_SHARD_QUEST)) {
      return;
   }

   shard = clone_object(NOKICLIFFS_CHAOS_SHARD);
   shard->setup();
   if (shard->move(killer)) {
      killer->message("A shard of chaos passes into your possession.\n");
   }
}

int damage_hook(object victim, object weapon, int damage) {
   return ::damage_hook(victim, weapon, damage);
}

int after_damage_hook(object aggressor, object weapon, int damage) {
   object law_shard;
   int    weapon_is_lawbringer;

   law_shard = aggressor->present("lawshard");
   weapon_is_lawbringer = weapon && weapon->query_id() == "lawbringer" &&
      weapon->is_wielded();

   if (nilp(law_shard) && !weapon_is_lawbringer) {
      aggressor->message("You need the law on your side!");
      halt_fight();
      aggressor->halt_fight();
      return 0;
   }

   return damage;
}

void setup(void) {
   set_name("chaosdemon");
   set_short("A chaosdemon");
   set_long("This is a demon of chaos. It is not evil, not good, not " +
      "neutral. It is -- chaotic. It shimmers and wavers like a cloud " +
      "of poison gas, but you can still make out some features, like the " +
      "gleeming teeth, the dangerously glowing eyes, and the " +
      "industrial strength muscles in what should probably be called " +
      "arms. This creature looks very powerful, and clearly a very " +
      "special weapon is needed if you want to hurt it.");
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_race("demon");
   set_hit_skill("combat/edge/large");
   set_skill("combat/edge/large", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE * 8);
   set_spell_chance(50);
   set_spell_damage(1);
   set_spell_message("The chaosdemon casts a SEVERE INTERNAL " +
      "DAMAGE AND PAIN spell at $t.\n");
   equip_monster(({ NOKICLIFFS_WEAPONS_DIR + "/chaosblade.c" }));
}
