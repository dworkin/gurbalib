#include "../../domain.h"

inherit "/std/room";
inherit DIR + "/lib/maze";

void setup(void) {
   add_area("2.4.5");

   set_short("End of the maze");
   set_long("Congratulations you have done it.");

   add_exit("south", DIR + "/rooms/maze1/maze4.c");

   set_objects (DIR + "/obj/leather.c");
}
