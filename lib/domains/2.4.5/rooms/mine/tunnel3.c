#include "../../domain.h"

inherit "/std/room";
inherit DIR + "/lib/climb_rope";

void setup(void) {
   add_area("2.4.5");

   set_short("Hole");
   set_long("There is a giant hole in the ground here, " +
      "and a large iron ring attached to the wall.");

   add_exit("north", DIR + "/rooms/mine/tunnel4.c");
   add_exit("south", DIR + "/rooms/mine/tunnel2.c");

   add_action("do_tie", "tie");
   add_action("do_untie", "untie");
   add_action("do_climb", "climb");

   add_item("ring", "A large iron ring hooked to the wall. " +
      "You could probably tie a rope to it.");
   add_item("hole", "The hole looks very deep an looks unsafe.");
   set_rooms_to_notify(( {
         DIR + "/rooms/mine/tunnel8", DIR + "/rooms/mine/tunnel9"})
      );
}

int do_climb(string str) {
   if (query_tied()) {
      move_player(this_player(), this_object(), "down",
         DIR + "/rooms/mine/tunnel8.c");
   } else {
      write("You would fall down the hole and possibly hurt yourself.\n");
      tell_room(this_player(), this_player()->query_Name() +
         " attempts to go down the hole and fails.\n");
   }
   return 1;
}
