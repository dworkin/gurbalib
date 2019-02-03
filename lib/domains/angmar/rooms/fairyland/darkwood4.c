#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_light(0);
   set_short("Walking in Darkwood");
   set_long("You are walking somewhere in Darkwood. " +
            "It's almost pitch black. Are there any " +
            "nasty monsters lurking around here?");

   add_exit("north", FAIRYLAND_ROOMS + "/dw_path4.c");

   set_objects(DIR + "/monsters/witch.c");
}
