#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Inside the chapel of the Abbey of Law");
   set_long("You are standing inside of the abbey's chapel. " +
      "The chapel is fairly small and has no windows here for to " +
      "prevent the faithful from distractions of the outside world.");

   set_exits(([
      "west" : DIR + "/rooms/abbey_of_law/outside_chapel.c"
   ]));

   set_objects(DIR + "/monsters/paladin.c");
}
