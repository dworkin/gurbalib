#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Mountain pass");
   set_long("You are in a pass going into the mountain with a steep " +
     "slope upwards to the north.  However, the path is barred.  There " +
     "is a tunnel entrance to the north.  It might be possible to climb " +
     "up, though.");

   add_exit("north", DIR + "/rooms/vill_shore.c");
   add_room_command("climb","do_climb");
}

int do_climb(string str) {
   object old_room;
   if (str == "" || str == "up") {
         old_room = this_player()->query_environment();
         this_player()->move(DIR + "/rooms/ravine.c");
         write("You climb up the hill.\n");
         tell_room(this_player(), this_player()->query_Name() + 
            " climbs up the ravine.\n");
         this_player()->query_environment()->tell_room(this_player(),
            this_player()->query_Name() + " climbs up the ravine.\n");
         this_player()->do_look(0);
      return 1;
   }
   return 0;
}
