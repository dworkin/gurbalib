#include "../domain.h"

inherit DIR + "/lib/undead";

private arm_weapon() {
	object sword;

	sword = clone_object(NOKICLIFFS_WEAPONS_DIR + "/ataghan");
	sword->setup();
	sword->move(this_object());
	do_wield(sword);
}

private arm() {
	arm_weapon();
}

void setup() {
   set_name("paladin");
   set_gender("male");
   set_short("Paladin (undead)");
   set_long("The brain's guard. He is a hulking beast with a " +
      "permanent demonic snarl revealing disgusting brown " +
      "teeth. Protruding from his forehead are two large " +
      "gently curved horns. His skin is a deep blood red " +
      "colour. He is clearly not pleased by your " +
      "presence here so close to his master, the brain.");
   set_level(40);
   set_skill("combat/defense", 200);
	set_skill("combat/sharp/medium", 200);

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

