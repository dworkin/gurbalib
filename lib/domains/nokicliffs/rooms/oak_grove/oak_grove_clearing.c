#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("A clearing in the oak grove pocket dimension");
   set_long("You are in a small clearing of the oak " +
      "grove. This is truly hallowed ground upon which " +
      "you stand. For millenia the fae have come here " +
      "to worship the Ancient One.");

   set_exits(([
      "south" : DIR + "/rooms/oak_grove/oak_grove_middle.c"
   ]));

   set_objects(DIR + "/obj/ancient_pedestal.c");
}
