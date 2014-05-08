#include "../domain.h"

inherit "/std/monster";

#define INTERVAL 8
static int count;

void do_extra_actions() {
   if (++count >= INTERVAL) {
      respond("hiss");
      count = 0;
   }
}

void setup() {
	set_name("apep");
	add_id("serpent", "chaosserpent", "chaos serpent");
	set_short("Apep the chaos serpent");
	set_long("Apep the chaos serpent is a giant beast with a strong " +
		"hiss and long sharp fangs that look like they hit hard.");
	set_race("demon");
	set_level(50);
	set_hit_skill("combat/unarmed");
	set_skill("combat/defense", 1);
	set_skill("combat/unarmed", 200);
	set_aggressive(0);
	set_spell_chance(50);
	set_spell_damage(1);
	set_spell_message("Apep casts a chaotic brain scrambling spell at $t.");
	set_hit_string("bite");
}

