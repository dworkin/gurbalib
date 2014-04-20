#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Lair of the giant");
   set_long("There are mountains all around you.");

   add_exit("east", DIR + "/rooms/giant_path.c");
   add_exit("west", DIR + "/rooms/giant_conf.c");

   set_objects (DIR + "/monsters/giant.c");
}
