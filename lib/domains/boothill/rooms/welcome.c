#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("Welcome to town");
   set_long("A large sign stretches across the road.  It reads: \"Welcome " +
      "to town\".  The road north, bends to the west here.");

   set_exits(([
      "north" : DIR + "/rooms/infront_saloon.c",
      "south" : DIR + "/rooms/entrance.c", 
   ]));
}
