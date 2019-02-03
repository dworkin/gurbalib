#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("Top of stairs");
   set_long("You are at the top of a long staircase going down into the lower "
        + "regions of the castle. You peer into the darkness below, but "
        + "can see nothing.");
   
   add_exit("down", CASTLE_ROOMS + "/midstairs.c");
   add_exit("north", CASTLE_ROOMS + "/inside.c");

   add_item("stairs", "They look slippery, but it should be relatively safe climbing down.");
   add_item("staircase", "The staircase winds its way into the nether regions of the castle.");
   add_item("castle", "The castle seems eerie as it envelopes you in its dark folds.");
}
