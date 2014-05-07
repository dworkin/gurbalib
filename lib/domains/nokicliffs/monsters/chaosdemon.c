#include "../domain.h"

inherit "/std/monster";

int damage_hook(object victim, object weapon, int damage) {
	return ::damage_hook(victim, weapon, damage);
}

private void arm() {
	object chaosblade;
	chaosblade = present("chaosblade");
	if (chaosblade) {
		do_wield(chaosblade);
		return;
	}
	chaosblade = clone_object(NOKICLIFFS_CHAOSBLADE);
	chaosblade->setup();
	chaosblade->move(this_object());
	do_wield(chaosblade);
}

void setup() {
	set_name("chaosdemon");
	set_short("A chaosdemon");
	set_long("This is a demon of chaos. It is not evil, not good, not " +
		"neutral. It is -- chaotic. It shimmers and wavers like a cloud " +
		"of poison gas, but you can still make out some features, like the " +
		"gleeming teeth, the dangerously glowing eyes, and the "+
		"industrial strength muscles in what should probably be called " +
		"arms. This creature looks very powerful, and clearly a very " +
		"special weapon is needed if you want to hurt it.");
	set_race("demon");
	set_level(40);
	set_hit_skill("combat/unarmed");
	set_skill("combat/defense", 100);
	set_skill("combat/sharp/large", 200);
	set_aggressive(0);
	set_spell_chance(50);
	set_spell_damage(30);
	set_spell_message("The chaosdemon casts a SEVERE INTERNAL " +
		"DAMAGE AND PAIN spell at $t.\n");
	arm();
}

