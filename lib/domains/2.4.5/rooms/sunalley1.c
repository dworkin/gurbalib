#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Sun alley");
   set_long("Sun alley runs east-west.");

   add_exit("east", DIR + "/rooms/eastroad3.c");
   add_exit("west", DIR + "/rooms/sunalley2.c");
}
