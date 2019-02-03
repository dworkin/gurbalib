#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("Somewhere in Darkwood");
   set_long("You are walking somewhere in Darkwood. " +
      "You jump at the sound of a twig snapping.");

   add_exit("west", FAIRYLAND_ROOMS + "/dw_path2.c");

   add_item("twig", "A small piece of wood. If you were trying to be silent, you blew it.");
}
