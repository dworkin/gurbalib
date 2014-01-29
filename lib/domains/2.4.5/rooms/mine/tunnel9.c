#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Hole in ceiling");
   add_exit("east", DIR + "/rooms/mine/tunnel14.c");
   add_exit("west", DIR + "/rooms/mine/tunnel10.c");
   add_action("do_up", "up");
   add_action("do_up", "climb");
}

string query_long() {
   if (!call_other(DIR + "/rooms/mine/tunnel3","query_tied")) {
      return "There is a big hole in the ceiling.";
   } else {
      return "There is a big hole in the ceiling, " +
         "with a rope hanging down from it.";
   }
}

int do_up(string str) {
   if (str == "rope" || str == "up") { 
      if (!call_other(DIR + "/rooms/mine/tunnel3","query_tied")) {
         write("You can not climb up, there is not a rope.\n");
      } else {
         this_player()->move(DIR + "/rooms/mine/tunnel8.c");
         write("You climb up the rope.\n");
         tell_room(this_player(),
            this_player()->query_Name() + " climbs up the rope.\n");
         this_player()->query_environment()->tell_room(this_player(),
            this_player()->query_Name() + " climbs up the rope.\n");
         this_player()->do_look(0);
      }
      return 1;
   }
   return 0;
}
