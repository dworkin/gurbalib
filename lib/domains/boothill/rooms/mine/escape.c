#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("Escape");
   set_long("After walking down an endless mine shaft, you finally see the " +
      "light at the end of the tunnel.  There is a hole to the east.  " +
      "To the west the mine crawls deeper into the mountain.");

   add_action("move_rubble", "move");

   add_item("rubble", "The wall has a bunch of rocks.  It looks like " +
      "you might be able to move it.");

   set_exits(([
      "west" : DIR + "/rooms/mine/mineshaft.c",
   ]));
}

int move_rubble(string str) {
   if (str == "rubble") {
      write("You rummage around in the rubble and slide through to " +
         "the other side.");
      this_environment()->tell_room(this_player(), this_player()->query_Name() +
         " digs through the rubble and disappears.");

      this_player()->move(DIR + "/rooms/mntpath.c");
      return 1;
   } 
   return 0;
}
