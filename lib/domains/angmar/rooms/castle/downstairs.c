#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("Bottom of staircase");
   set_long("You are at the bottom of the staircase. Nobody has been here for "
        + "a long time. Still, the place is lit up by torches. The atmosphere "
        + "does not feel very good. You can easily imagine evil creatures "
        + "lurking in every corner. ");
   
   add_exit("up", CASTLE_ROOMS + "/midstairs");
   add_exit("east", CASTLE_ROOMS + "/corridor");
   add_exit("south", CASTLE_ROOMS + "/torture");

   add_item("torches", "The torches are fastened to the wall. They seem to be magical");
   add_item("creatures", "See?  Your imagination is flourishing");
   add_item("corners", "You search them, but find nothing");
   add_item("staircase", "The staircase winds its way back up into the castle");

   set_objects(DIR + "/monsters/bat.c");
}
