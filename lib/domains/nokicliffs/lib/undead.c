#include "../domain.h"

inherit "/std/monster";

int is_undead() {
	return 1;
}

void setup() {
	add_vulnerability("holy");
}

