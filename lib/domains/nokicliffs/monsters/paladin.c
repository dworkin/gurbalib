#include "../domain.h"

inherit DIR + "/lib/undead";

private void move_object_here(object obj) {
	obj->setup();
	obj->move(this_object());
}

private void wear_object(object obj) {
	move_object_here(obj);
	do_wear(obj);
}

private void wield_object(object obj) {
	move_object_here(obj);
	do_wield(obj);
}

private arm() {
	if (!present("crown")) {
		wear_object(clone_object(NOKICLIFFS_ARMOURS_DIR + "/crown"));
	}
	if (!present("gloves")) {
		wear_object(clone_object(NOKICLIFFS_ARMOURS_DIR + "/leather_gloves"));
	}
	if (!present("cuirass")) {
		wear_object(clone_object(NOKICLIFFS_ARMOURS_DIR + "/cuirass"));
	}
	if (!present("tower shield")) {
		wield_object(clone_object(NOKICLIFFS_ARMOURS_DIR + "/tower_shield"));
	}
	if (!present("ataghan")) {
		wield_object(clone_object(NOKICLIFFS_WEAPONS_DIR + "/ataghan"));
	}
	if (!present("lawbringer")) {
		move_object_here(clone_object(NOKICLIFFS_WEAPONS_DIR + "/lawbringer"));
	}
}

void setup() {
	::setup();
   set_name("paladin");
   set_gender("male");
   set_short("Paladin (undead)");
   set_long("Strong magic has cursed the paladin to live in " +
		"undeath. It has utterly transformed this man into a " +
		"terrible and ugly monster. In older days this man was " +
		"a law bringer keeping the realms safe from chaos. His " +
		"long ago lost their light now his soul seeks to rest in " +
		"peace.");
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

