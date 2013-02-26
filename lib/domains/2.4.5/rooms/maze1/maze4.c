#include "../../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_short("In a maze");
   set_long("There are four obvious exits: north, south, east, west");

}

/* XXX Need to figure out fake exits... */
int do_movement() {
   exit_num = random(4);
   if (exit_num == 2) {
      room = DIR + "/rooms/maze1/maze5.c";
   } else {
      room = DIR + "/rooms/maze1/maze3.c";
   }

}

int do_movement2() {
   exit_num = random(4);
   if (exit_num == 2) {
      room = DIR + "/rooms/maze1/maze5.c";
   } else {
      room = DIR + "/rooms/well.c";
   }

}
