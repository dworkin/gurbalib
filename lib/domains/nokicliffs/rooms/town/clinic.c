#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town medical clinic");
   set_long("You are at Noki Town's medical clinic. " +
      "Go east to return to " +
      "to the public bath. If the nurse is in, see " +
      "what's on sale with the 'list' command.");
   set_exits(([
      "east" : DIR + "/rooms/town/public_bath.c"
   ]));
   set_objects(NOKICLIFFS_TOWN_NURSE);
}
