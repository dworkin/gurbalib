#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Focus Point");
   set_long("You are standing in a small grove on the western most " +
      "point of the Isle of the Magi, Focus Point.  All of the trees " +
      "here are either diseased, dead or heavily mutated.  " +
      "On the very end of the point stands an old, crumbling stone pedestal. " +
      " Legend has it that Arcanarton mounted some sort of a magic focusing " +
      "device here, and used the energy it collected to increase the " +
      "power of his spells.  The device is now nowhere to be found.  " +
      "The shore of the island continues east and southeast into a small " +
      "grove from here.");

   add_exit("east", DIR + "/rooms/south/sislnd11.c");
   add_exit("southeast", DIR + "/rooms/south/sislnd9.c");
}
