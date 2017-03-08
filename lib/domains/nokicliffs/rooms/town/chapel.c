#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town chapel");
   set_long("You are in the Noki Town chapel. " +
      "Villagers come here to meditate and be at peace " +
      "with the multiverse. There " + 
      "is plenty of seating so take a load off for a " +
      "while and enjoy the peace and quiet when there is " +
      "not a wedding ceremony going on, of course.");
   set_exits(([
      "west" : DIR + "/rooms/town/square_middle.c"
   ]));
   set_objects(DIR + "/obj/donation_box.c");
}

