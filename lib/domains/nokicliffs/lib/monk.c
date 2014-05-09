#include "../domain.h"

inherit "/std/monster";

static nomask void wear_object(object obj) {
	obj->setup();
	obj->move(this_object());
	do_wear(obj);
}

static nomask void clothe() {
	if (!present("robe")) {
		wear_object(clone_object(NOKICLIFFS_ARMOURS_DIR + "/monk_robe"));
	}
	if (!present("sandals")) {
		wear_object(clone_object(NOKICLIFFS_ARMOURS_DIR + "/monk_sandals"));
	}
	if (!present("rope belt")) {
		wear_object(clone_object(NOKICLIFFS_ARMOURS_DIR + "/rope_belt"));
	}
}

void setup() {
   set_gender("male");
	clothe();
}

