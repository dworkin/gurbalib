#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("The entrance to Darkwood");
   set_long("You are standing in front of the entrance to Darkwood. "
            + "You cannot see further than a few metres of the path "
            + "that is trailing into the forest.");

   add_exit("east", FAIRYLAND_ROOMS + "/dw_path1.c");
   add_exit("west", FAIRYLAND_ROOMS + "/path1.c");

   add_item("darkwood", "A dark and menacing forest. You don't want to enter it.");
   add_item("forest", "The trees themselves seem dark. Evil emanates from the heart of the forest.");
   add_item("trees", "No longer are they healthy trees. The dark has claimed them.");
   add_item("dark", "You cannot examine such an evil presence.");
   add_item("entrance", "The road blends into the wood, and disappears from view.");
   add_item("road", "It leads to the forest, but you cannot see further.");
   add_item("path", "It leads to the forest, but you cannot see further.");

   add_action("climb_cmd", "climb");

   set_objects(DIR + "/obj/signs/darkw_entrance.c");
}

int climb_cmd(string str) {
   if (str && (str == "trees" || str == "tree")) {
      this_player()->simple_action("$N $vthink about climbing a try, " +
         "but $vshiver involuntarily upon approach " +
         "and $vdare not try to climb.");
      return 1;
   }

   return 0;
}
