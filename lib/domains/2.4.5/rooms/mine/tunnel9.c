#include "../../domain.h"
#define UP_ROOM DIR + "/rooms/mine/tunnel8.c"

inherit "/std/room";
inherit DIR + "/lib/climb_rope";

void setup(void) {
   add_area("2.4.5");

   set_short("Hole in ceiling");
   set_long("You are in the bottom of a shaft in the tunnels. " +
      "There is a hole in the ceiling.");
   add_exit("east", DIR + "/rooms/mine/tunnel14.c");
   add_exit("west", DIR + "/rooms/mine/tunnel10.c");
   add_action("do_climb", "climb");
}

int is_rope() {
   return::is_rope(DIR + "/rooms/mine/tunnel3");
}

string query_long() {
   string str;

   str = ::query_long();
   if (is_rope()) {
      str += " " + query_extra_long(1, 0);
   }
   return str;
}

private void do_up(string str) {
   move_player(this_player(), this_object(), "up", UP_ROOM);
}

int do_climb(string str) {
   if (!is_rope()) {
      write("There is no rope to climb.");
      return 1;
   }
   if (str == "up" || str == "up rope") {
      do_up(str);
      return 1;
   }
   write("You should climb up, if you wish to climb the rope.");
   return 1;
}
