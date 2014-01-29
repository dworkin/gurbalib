#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Mountain pass");
   set_long("You are in a pass going into the mountain with a steep " +
     "slope upwards to the north.  However, the path is barred.  There " +
     "is a tunnel entrance to the north.  It might be possible to climb " +
     "up, though.");

   add_exit("north", DIR + "/rooms/mine/tunnel.c");
   add_exit("south", DIR + "/rooms/plain11.c");
   add_exit("up", "#do_climb"); 
   add_action("do_climb", "climb");
}

int do_climb(string str) {
   string usermsg, othermsg;

   usermsg = "You climb up the hill.";
   othermsg = this_player()->query_Name() + " climbs up the ravine.";

   /* XXX domove(DIR + "/rooms/ravine.c", usermsg, othermsg);  */
   return 1;
}
