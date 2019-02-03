#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town hotel lobby");
   set_long("You are in the lobby of the Noki Town hotel. " +
      "Even the locals like to rent out the exquisite rooms " +
      "here for a relaxing or romantic get-a-way. The " +
      "remainder of the rooms are occupied by the town's " +
      "transient population. As such, there is no vacancy " +
      "now. However, you are welcomed to enjoy the casino " +
      "down the grand staircase.");

   set_exits(([
      "down" : DIR + "/rooms/town/casino.c"
   ]));

   add_item("grand staircase", "It sure is grand. It was " +
      "built by Noki Town's finest carpenters, builders, and " +
      "artisans.");
   add_item("staircase", "It's a grand staircase built by Noki " +
      "Town's finest carpenters, builders, and artisans.");
}
