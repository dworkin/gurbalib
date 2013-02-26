#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_short("Giants conference of human bashing");
   set_long("You are at the yearly conference of human bashing, " +
      "organized by the giants");

   add_exit("east", DIR + "/rooms/giant_lair.c");

  set_objects (([
      DIR + "/monsters/fire_giant.c": 1,
      DIR + "/monsters/frost_giant.c": 1,
      DIR + "/monsters/stone_giant.c": 1,
   ]));

}
