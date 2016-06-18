inherit "/std/room";

#include "../domain.h"

void create(void) {
   ::create();
   add_area(NOKICLIFFS_AREA);
   add_area("2.4.5");
}

int ok_to_teleport(void) {
   return 1;
}

