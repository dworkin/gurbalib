#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("The beech woods");
   set_long("You are in the beech woods. The sun is shining through the foliage.");

   add_exit("north", FAIRYLAND_ROOMS + "/edge1.c");
   add_exit("south", FAIRYLAND_ROOMS + "/beech3.c");
   add_exit("west", FAIRYLAND_ROOMS + "/beech2.c");

   add_item("woods", "The woods consist of a huge number of beech trees.");
   add_item("trees", "Beech trees, which have been here for years.");
   add_item("beech trees", "Beech trees, which have been here for years.");
   add_item("sun", "The sun, rising over Mizar, peeks through the foliage.");
   add_item("foliage", "The branches of the beech trees mesh together.");
   add_item("branches", "They look too high to climb.");

   set_objects(DIR + "/monsters/elf.c");

   add_action("climb_cmd", "climb");
}

int climb_cmd(string str) {
   if (!empty_str(str) && (str == "tree" || str == "trees" || str == "beech tree" || str == "beech trees")) {
       this_player()->simple_action("$N $vtry to climb a tree but cannot reach the branches.");
       return 1;
   }

   return 0;
}
