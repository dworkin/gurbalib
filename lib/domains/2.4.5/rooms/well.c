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

   add_item("lever", "A short wooden handle, perhaps you can pull it.");
   add_item("door", "#do_look_door");

   add_action("pull_lever", "pull");
   add_action("pull_lever", "turn");

   add_block("west");
}

object load_traproom() {
   object traproom;
   string trapname;

   trapname = DIR + "/rooms/sub/door_trap";
   traproom = find_object(trapname);
   if (!traproom) {
      if (traproom = compile_object(trapname)) {
         traproom->setup();
         traproom->setup_mudlib();
      }
   }
   return traproom;
}

string do_look_door() {
   object traproom;

   traproom = load_traproom();
   if (!traproom || traproom->query_trap()) {
      return "The door is open.";
   } else {
      return "The door is closed.";
   }
}

int pull_lever(string str) {
   object traproom;

   if (empty_str(str) || str != "lever") {
      return 0;
   }

   traproom = load_traproom();

   if (!traproom) {
      write("The lever appears to be jammed.\n");
      tell_room(this_player(), this_player()->query_Name() +
         " attempts to pull the lever, but it's jammed.\n");
      return 0;
   }

   if (traproom->toggle_door()) {
      write("You pull the lever.\n");
      tell_room(this_player(), this_player()->query_Name() +
         " pulls the lever.\n");
      if (traproom->query_trap()) {
         tell_room(nil, "A bolt slides into place.\n");
      } else {
         tell_room(nil, "A bolt slides out of place.\n");
      }
      return 1;
   }
   return 0;
}

int do_block(object who) {
   object traproom;

   traproom = load_traproom();

   if (!traproom || !traproom->query_trap()) {
      write("The door is blocked.\n");
      return 1;
   } else {
      return 0;
   }
}

int do_open(string str) {
   object traproom;

   if (str == "door") {
      traproom = load_traproom();
      if (!traproom || traproom->query_trap()) {
         write("The door is already open.");
         tell_room(this_player(), this_player()->query_Name() + " tugs " +
            "at the open door.\n");
         return 1;
      }
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

