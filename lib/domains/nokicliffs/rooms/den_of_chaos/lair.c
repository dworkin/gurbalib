#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_light(0);
   set_short("The lair of the Chaosdemon in the Den of Chaos in a " + 
      "pocket dimension");
   set_long("You are standing in the " +
      "lair of the uber chaotic Chaosdemon. You feel the urge to bring " +
      "law to this place and thereby restore the balance. The lair itself " +
      "is far too chaotic for to understand, let alone explain.");

   set_exits(([
      "west": DIR + "/rooms/den_of_chaos/cooridor_end.c"
   ]));

   set_objects(NOKICLIFFS_MONSTERS_DIR + "/chaosdemon");
}
