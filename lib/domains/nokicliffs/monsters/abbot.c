#include "../domain.h"

inherit DIR + "/lib/monk";

void setup() {
	::setup();
   set_name("abbot");
   set_short("The Abbot");
   set_long("The abbey's abbot. He is an older man, slightly " +
		"hunched. He is balding with a crescent of pure white hair " +
		"around the back of his head. He wears an old robe secured " +
		"with a simple rope. Upon his feet he wears sandals.");
   set_level(40);
   set_skill("combat/defense", 200);
	set_skill("combat/unarmed", 2);
	clothe();
}

