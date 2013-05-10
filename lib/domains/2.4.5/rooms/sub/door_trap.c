#include "../../domain.h"

inherit "/std/room";
inherit "/std/modules/m_block_exits";

int trap;

void setup(void) {
   add_area("2.4.5");

   set_short("Room wiht black walls");
   set_long("A room with black walls.  There is a door to the east, " +
      "and a door to the west.");

   /* Need to do door stuff here XXX */
   add_exit("east", DIR + "/rooms/well.c");
   add_exit("west", DIR + "/rooms/sub/after_trap.c");

   add_block("east");
}

int do_block(object who) {
   if (!trap) {
      write("The door is blocked.\n");
      return 1;
   } else {
      return 0;
   }
}

int toggle_door(string str) {
   write("You pull the lever.\n");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " pulls the lever.\n");
   if (trap) {
      trap = 0;
   } else {
      trap = 1;
   }
   return 1;
}

int query_trap(string str) {
   return trap;
}
