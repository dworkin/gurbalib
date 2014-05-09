#include "../domain.h"

inherit DIR + "/lib/undead";

private arm() {
	equip_monster(({
		NOKICLIFFS_ARMOURS_DIR + "/crown",
		NOKICLIFFS_ARMOURS_DIR + "/leather_gloves",
		NOKICLIFFS_ARMOURS_DIR + "/cuirass",
		NOKICLIFFS_ARMOURS_DIR + "/tower_shield",
		NOKICLIFFS_WEAPONS_DIR + "/ataghan"
	}));
}

void setup() {
	::setup();
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
   set_level(40);
   set_skill("combat/defense", 200);
	set_skill("combat/sharp/medium", 200);

	set_objects(NOKICLIFFS_WEAPONS_DIR + "/lawbringer");
	arm();
}

void monster_died() {
	object shard;
	if (nilp(killer) || killer->is_quest_completed(NOKICLIFFS_SHARD_QUEST)) {
		return;
	}
	shard = clone_object(NOKICLIFFS_LAW_SHARD);
	shard->setup();
	shard->move(killer);
	killer->message("A shard of law passes into your possession.\n");
}

