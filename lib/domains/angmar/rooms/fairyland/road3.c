#include "../../domain.h"

inherit "/std/room";

void setup(void) {
    add_area(AREA);
    add_area(FAIRYLAND_AREA);
    set_short("The small road");
    set_long("You are standing on a small road which continues to the north. " +
       "There is a meadow to the west.");

    add_exit("north", FAIRYLAND_ROOMS + "/crossing.c");
    add_exit("south", FAIRYLAND_ROOMS + "/road2.c");
    add_exit("west", FAIRYLAND_ROOMS + "/meadow.c");

    add_item("meadow", "The lush green grass and fresh air entice you to wander over there.");
    add_item("road", "The road seems to be narrowing down.");
}
