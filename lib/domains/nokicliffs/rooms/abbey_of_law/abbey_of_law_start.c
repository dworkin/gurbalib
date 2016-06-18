#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("The Abbey of Law in a pocket dimension.");
   set_long("You can 'leave' the pocket dimension. " +
      "Ideally it will return you to the room you " +
      "arrived from; if it is not found, then you " + "go to the base camp.");

   set_exits((["east": DIR + "/rooms/abbey_of_law/lobby.c",
      "leave":NOKICLIFFS_BASE_CAMP]));
}
