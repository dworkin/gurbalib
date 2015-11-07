#include "../../domain.h"
#define UP_ROOM DIR + "/rooms/mine/tunnel3.c"
#define DOWN_ROOM DIR + "/rooms/mine/tunnel9.c"

inherit "/std/room";
inherit DIR + "/lib/climb_rope";

void setup(void) {
   add_area("2.4.5");

   set_short("Shaft");
   set_long("In a shaft going straight down.");

   add_action("do_climb", "climb");
}

int is_rope() {
   return::is_rope(DIR + "/rooms/mine/tunnel3");
}

string query_long() {
   string str;
   str = ::query_long();
   if (is_rope()) {
      str += " " + query_extra_long(1, 1);
   }
   return str;
}

private void do_up(string str) {
   move_player(this_player(), this_object(), "up", UP_ROOM);
}

private void do_down(string str) {
   move_player(this_player(), this_object(), "down", DOWN_ROOM);
}

int do_climb(string str) {
   if (!is_rope()) {
      write("There is no rope here to climb.");
      return 1;
   }
   if (empty_str(str)) {
      write("In which direction?");
      return 1;
   }
   if (str == "up" || str == "up rope") {
      do_up(str);
      return 1;
   }
   if (str == "down" || str == "down rope") {
      do_down(str);
      return 1;
   }
   write("You should climb up or climb down, if you wish to climb.");
   return 1;
}
