#include "../../domain.h"

inherit "/std/room";

static int box_flag;
static int fish_flag;

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_short("In a clump of reeds");
   set_long("You trudge through the reeds, and find yourself in a small "
            + "fishing area. Reeds and other water plants have been cleared "
            + "away to form a small spot to sit and fish, if you don't mind "
            + "getting your pants wet.");

   add_exit("west", FAIRYLAND_ROOMS + "/by_lake.c");

   add_item("plants", "All sorts of water plants, algae, and tubes grow here.");
   add_item("reeds", "Small green tubes, growing from the bottom of the lake.");
   add_item("bottom", "You search the bottom, but only find reed roots.");
   add_item("lake", "The lake is tranquil and calm; the perfect place to fish.");

   box_flag = 1;
   fish_flag = 1;
}

string fish(object angler) {
   object obj;

   if (box_flag) {
      obj = clone_object(DIR + "/obj/box.c");
      obj->setup();
      obj->move(this_object());
      box_flag = 0;
      return "$N $vsnag something metal while fishing.";
   }

   if (fish_flag) {
      obj = clone_object(DIR + "/obj/cauldron/dead_fish.c");
      obj->setup();
      obj->move(this_object());
      fish_flag = 0;
      return "$N $vcatch a dead fish.";
   }

   return "$N $vfail to catch anything. Better luck next time.";
}
