#include "../domain.h"

inherit DIR + "/lib/undead";

private void add_lawbringer(void) {
   object obj;

   if (present("lawbringer")) {
      return;
   }

   obj = clone_object(NOKICLIFFS_WEAPONS_DIR + "/lawbringer");
   obj->setup();
   obj->move(this_object());
}

private void arm(void) {
   equip_monster(({
      NOKICLIFFS_ARMORS_DIR + "/crown",
      NOKICLIFFS_ARMORS_DIR + "/leather_gloves",
      NOKICLIFFS_ARMORS_DIR + "/cuirass",
      NOKICLIFFS_ARMORS_DIR + "/tower_shield",
      NOKICLIFFS_WEAPONS_DIR + "/ataghan",
   }));
   add_lawbringer();
}

void setup(void) {
   set_name("paladin");
   set_gender("male");
   set_short("Paladin (undead)");
   set_long("Strong magic has cursed the paladin to live in " +
      "undeath. It has utterly transformed this man into a " +
      "terrible and ugly monster. In older days this man was " +
      "a law bringer keeping the realms safe from chaos. His eyes " +
      "long ago lost their light now his soul seeks to rest in " +
      "peace. However, despite this terrible fate, the law is " +
      "still very great within him.");
   arm();
   add_coins("royal", 1 + random(5));
   set_hit_skill("combat/edge/medium");
   set_skill("combat/edge/medium", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE * 7);
}

void monster_died(void) {
   object shard;

   if (nilp(killer) || killer->is_quest_completed(NOKICLIFFS_SHARD_QUEST)) {
      return;
   }

   shard = clone_object(NOKICLIFFS_LAW_SHARD);
   shard->setup();
   if (shard->move(killer)) {
      killer->message("A shard of law passes into your possession.\n");
   }
}
