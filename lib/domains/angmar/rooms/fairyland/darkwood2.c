#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("Somewhere deep inside Darkwood");
   set_long("You are walking somewhere in Darkwood. " +
            "You feel cold and frightened. " +
            "Maybe you should turn back?");

   add_exit("south", FAIRYLAND_ROOMS + "/dw_path3.c");
   add_exit("west", FAIRYLAND_ROOMS + "/darkwood3.c");

   add_item("darkwood", "You see something creep behind you out of the corner of your eye.");
   add_item("something", "It's gone now. Too fast for your untrained vision.");
}
