#include "../../domain.h"

inherit "/std/room";
inherit "/std/modules/m_block_exits";

int trap;

void setup(void) {
   add_area("2.4.5");

   set_short("Room with black walls");
   set_long("A room with black walls.  There is a door to the east, " +
      "and a door to the west.");

   add_exit("east", DIR + "/rooms/well.c");
   add_exit("west", DIR + "/rooms/sub/after_trap.c");

   add_item("door", "#do_look_door");

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

int toggle_door(void) {
   if (trap) {
      trap = 0;
   } else {
      trap = 1;
   }
   return 1;
}

int query_trap(void) {
   return trap;
}

string do_look_door() {
   if (query_trap()) {
      return "The door is open.";
   } else {
      return "The door is closed.";
   }
}

int do_open(string str) {
   if (str == "door") {
      write("The door doesn't seem to work that way.\n");
      tell_room(this_player(), this_player()->query_Name() +
         " looks at the door in confusion.\n");
      return 1;
   }
   return 0;
}

int do_close(string str) {
   return do_open(str);
}
