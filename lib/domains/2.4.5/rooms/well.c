#include "../domain.h"

inherit "/std/room";
inherit "/std/modules/m_block_exits";

void setup(void) {
   add_area("2.4.5");

   set_short("Down the well");
   set_long("You are down the well.  It is wet and slippery.  " +
      "There is a lever beside a door to the west.");

   add_exit("north", DIR + "/rooms/maze/maze1.c");
   add_exit("west", DIR + "/rooms/sub/door_trap.c");
   add_exit("up", DIR + "/rooms/narr_alley.c");

   add_item("lever", "A short wooden handle, prehaps you can pull it.");

   add_room_command("pull", "pull_lever");
   add_room_command("turn", "pull_lever");

   add_block("west");
}

/* XXX Need to add the lever and do what it does... */

int pull_lever(string str) {
   if (!str || str != "lever") return 0;
   if (call_other(this_player(),DIR + "/rooms/sub/door_trap", "toggle_door")) {
      return 1;
   }
   return 0;
}

int do_block(object who) {
   if (!call_other(this_player(),DIR + "/rooms/sub/query_trap", "query_trap")) {
      write("The door is blocked.\n");
      return 1;
   } else {
      return 0;
   }
}
