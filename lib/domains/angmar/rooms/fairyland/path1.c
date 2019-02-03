#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_short("The path to Misty Mountain");
   set_long("You are on the path to Misty Mountain. Many people have walked " +
      "this path. Not many have returned... The entrance to Darkwood is to " +
      "the east.");

   add_exit("south", FAIRYLAND_ROOMS + "/crossing.c");
   add_exit("east", FAIRYLAND_ROOMS + "/darkw_entrance.c");
   add_exit("west", FAIRYLAND_ROOMS + "/path2.c");

   add_item("entrance", "The entrance to Darkwood seems evil and forboding");
   add_item("darkwood", "The evil forest reeks of malignant airs...beware");
   add_item("forest", "Darkwood, the mystical forest of pure evil");
   add_item("path", "The path leads to Misty Mountain");
   add_item("misty mountain", "The mountain seems huge, even though you are far away from it");
   add_item("mountain", "The mountain seems huge, even though you are far away from it");
}
