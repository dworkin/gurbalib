#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   ::setup();

   set_short("Oak grove in a pocket dimension.");
   set_long("You can 'leave' the pocket dimension. " +
      "Ideally it will return you to the room you " +
      "arrived from; if it is not found, then you " + "go to the base camp.");

 set_exits((["north": DIR + "/rooms/oak_grove/oak_grove_middle.c", "leave":NOKICLIFFS_BASE_CAMP]));
}
