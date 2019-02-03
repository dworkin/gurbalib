#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("Edge of the woods");
   set_long("You are at the edge of the beech woods. The birds are singing.");

   add_exit("south", FAIRYLAND_ROOMS + "/beech2.c");
   add_exit("east", FAIRYLAND_ROOMS + "/edge1.c");

   add_item("edge", "The road blends into the woods here.");
   add_item("woods", "Dozens of beech trees, as far as the eye can see.");
   add_item("beech trees", "Magnificent fauna, watching the land.");
   add_item("sounds", "The sounds of a bird who is content.");

   add_action("listen_cmd", "listen");
   add_action("climb_cmd", "climb");
}

int listen_cmd(string str) {
   if (!empty_str(str) && (str == "birds" || str == "to the birds")) {
       this_player()->simple_action("$N $vlisten to the birds singing.");
       return 1;
   }

   return 0;
}

int climb_cmd(string str) {
   if (!empty_str(str) && (str == "trees" || str == "tree")) {
      this_player()->simple_action("$N $vfail to climb the tree.");
      return 1;
   }

   return 0;
}
