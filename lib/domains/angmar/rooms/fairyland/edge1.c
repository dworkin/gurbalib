#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("Edge of the woods");
   set_long("You are at the edge of the beech woods. The birds are singing cheerfully.");

   add_exit("north", FAIRYLAND_ROOMS + "/road1.c");
   add_exit("south", FAIRYLAND_ROOMS + "/beech1.c");
   add_exit("west", FAIRYLAND_ROOMS + "/edge2.c");

   add_item("tree", "You see a prime candidate for climbing.");
   add_item("edge", "The road blends into the woods here.");
   add_item("woods", "Dozens of beech trees, flourishing in their environment.");
   add_item("beech trees", "Standing tall, their branches sway in the wind.");
   add_item("trees", "Standing tall, their branches sway in the wind.");
   add_item("branches", "None of them look stable enough to hold you.");
   add_item("birds", "The birdsong pierces the air, and adds to the atmosphere.");

   add_action("listen_cmd", "listen");
   add_action("climb_cmd", "climb");
}

int listen_cmd(string str) {
   if (!empty_str(str) && (str == "birds" || str == "to the birds")) {
       this_player()->simple_action("$N $vlisten to the birds singing cheerfully.");
       return 1;
   }

   return 0;
}

int climb_cmd(string str) {
   if (!empty_str(str) && (str == "trees" || str == "tree")) {
      this_player()->simple_action("$N $vtry $p best, but cannot climb the tree.");
      return 1;
   }

   return 0;
}
