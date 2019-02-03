#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("Somewhere deep inside Darkwood");
   set_long("You are walking somewhere in Darkwood. " +
            "Are you lost?");

   add_exit("south", FAIRYLAND_ROOMS + "/dw_path4.c");
   add_exit("east", FAIRYLAND_ROOMS + "/darkwood2.c");
   add_exit("west", FAIRYLAND_ROOMS + "/darkwood5.c");
}
