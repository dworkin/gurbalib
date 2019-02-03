#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("On a path in Darkwood");
   set_long("You are on a twisty path in the legendary Darkwood. " +
      "Many adventurers have been killed here.");

   add_exit("north", FAIRYLAND_ROOMS + "/dw_path2.c");
   add_exit("west", FAIRYLAND_ROOMS + "/darkw_entrance.c");

   add_item("path", "The path twists and turns as it weaves its way into Darkwood.");
   add_item("darkwood", "The mystical forest makes you shudder as it emanates evil.");
}
