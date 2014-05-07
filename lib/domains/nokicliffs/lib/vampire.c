#include "../domain.h"

inherit DIR + "/lib/undead";

int is_vampire() {
	return 1;
}

void setup() {
	::setup();
	set_race("vampire");
	add_bane("garlic");
	add_vulnerability("silver");
}

