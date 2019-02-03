#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("The beech woods");
   set_long("You are in the beech woods. The birds are singing.");

   add_exit("north", FAIRYLAND_ROOMS + "/beech1.c");

   add_item("sun", "That's a terrible idea.");
   add_item("woods", "The woods consist of a huge number of beech trees.");
   add_item("trees", "Beech trees, which have been here for years.");
   add_item("beech trees", "Beech trees, which have been here for years.");
   add_item("sun", "The sun, rising over Mizar, peeks through the foliage.");
   add_item("foliage", "The branches of the beech trees mesh together.");
   add_item("branches", "They look too high to climb.");
   add_item("birds", "They flit away before you can glimpse them.");

   set_objects(DIR + "/monsters/elf_king.c");

   add_action("climb_cmd", "climb");
   add_action("listen_cmd", "listen");
}

int climb_cmd(string str) {
   if (!empty_str(str) && (str == "tree" || str == "trees" || str == "beech tree" || str == "beech trees")) {
      this_player()->simple_action("$N $vtry to climb a tree but cannot reach the branches.");
      return 1;
   }

   return 0;
}

int listen_cmd(string str) {
   if (!empty_str(str) && (str == "birds" || str == "to the birds")) {
      this_player()->simple_action("$N $vlisten to the birds contently singing.");
      return 1;
   }

   return 0;
}
