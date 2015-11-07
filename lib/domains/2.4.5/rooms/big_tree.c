#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Big tree");
   set_long("A big single tree on the plain.");

   add_exit("east", DIR + "/rooms/plain7.c");
   add_exit("west", DIR + "/rooms/giant_path.c");

   add_item("tree", "The branches are very high up.");

   add_action("climb", "climb");

   set_objects (DIR + "/obj/rope.c");
}

int climb(string arg) {
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " looks up at the tree.\n");
   write("There are no branches low enough for you to grab a hold of.\n");
   return 1;
}
