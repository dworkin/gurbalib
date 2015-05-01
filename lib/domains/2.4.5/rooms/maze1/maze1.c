#include "../../domain.h"

inherit "/std/room";
inherit DIR + "/lib/maze";

void setup(void) {
   add_area("2.4.5");

   set_short("In a maze");
   set_long("There are four obvious exits: north, south, east, west");
   add_exit("north", "#do_movementn");
   add_exit("south", "#do_movements");
   add_exit("east", "#do_movemente");
   add_exit("west", "#do_movementw");

}

void do_movementn() {
   string room;
   int exit_num;

   exit_num = random(4);
   if (exit_num == 2) {
      room = DIR + "/rooms/maze1/maze2.c";
   } else {
      room = DIR + "/rooms/well.c";
   }

   goto_the(room, "north");
}

void do_movements() {
   string room;
   int exit_num;

   exit_num = random(4);
   if (exit_num == 2) {
      room = DIR + "/rooms/maze1/maze2.c";
   } else {
      room = DIR + "/rooms/well.c";
   }

   goto_the(room, "south");
}

void do_movemente() {
   string room;
   int exit_num;

   exit_num = random(4);
   if (exit_num == 2) {
      room = DIR + "/rooms/maze1/maze2.c";
   } else {
      room = DIR + "/rooms/well.c";
   }

   goto_the(room, "east");
}

void do_movementw() {
   string room;
   int exit_num;

   exit_num = random(4);
   if (exit_num == 2) {
      room = DIR + "/rooms/maze1/maze2.c";
   } else {
      room = DIR + "/rooms/well.c";
   }

   goto_the(room, "west");
}
