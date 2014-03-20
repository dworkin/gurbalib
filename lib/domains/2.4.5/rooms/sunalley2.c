#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Sun alley");
   set_long("Sun alley runs east from here.");

   add_exit("east", DIR + "/rooms/sunalley1.c");
}
