#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("Between the staircases");
   set_long("You are between two long staircases going up and down. Torches on the " +
      "walls light up the passage. You wonder who keeps the torches lit. The " +
      "atmosphere somehow seems to become more threatening further down.");
   
   add_exit("up", CASTLE_ROOMS + "/stairs.c");
   add_exit("down", CASTLE_ROOMS + "/downstairs.c");
   add_exit("north", CASTLE_ROOMS + "/treasury_entrance.c");
   add_exit("west", CASTLE_ROOMS + "/magroom.c");

   add_item("staircases", "They wind their way into the castle, above and below you.");
   add_item("staircase", "It winds its way into the castle, above and below you.");
   add_item("torches", "They glow with a magical light. They seem not to need fuel.");
   add_item("sign", "The sign points west, and says, 'Fairyland'.");
}
