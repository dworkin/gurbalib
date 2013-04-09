#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GurbaSquare");
   add_area("GurbaOutdoor");

   set_short("Gurba Town Square - Southwest");
   set_long("The southwest corner of the town square is relatively " +
      "quiet.  A few benches are scattered around here for those who " +
      "need a break after visiting other parts of the square.  To the " +
      "north lies a sort of farmer's market, while to the east you can " +
      "hear distinct voices and occasional applause.  To the southwest " +
      "lies a small shop with a flower symbol over the door.");

   set_exits(([
      "east" : DIR + "/rooms/square_south",
      "north" : DIR + "/rooms/square_west",
      "northeast" : DIR + "/rooms/square_center",
      "southwest" : DIR + "/rooms/florist",
   ]));

   add_item("benches", "They're pretty standard wooden benches.  Nothing " +
      "exciting, really.");
}
