#include "../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Cliffs entrance area");
   set_long("To the east you can see the Noki Cliffs " +
      "looming large. There is a small plateau to the west.");

   set_exits(([
      "east" : DIR + "/rooms/cliffs/path.c",
      "west" : TWOFOURFIVE_DIR + "/rooms/mount_top2.c"
   ]));
}

