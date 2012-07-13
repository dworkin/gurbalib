#include "../../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Hole in ceiling");
   add_room_command("up","do_up");
}

string query_long() {
   if (!call_other(DIR + "/rooms/mine/tunnel3","query_tied")) {
      return "There is a big hole in the ceiling.";
   } else {
      return "There is a big hole in the ceiling, " +
         "with a rope hanging down from it.";
   }
}

void do_up() {
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
}
