#include "../../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("A cave passage in the Noki Cliffs filled with busts");
   set_long("This is a strange chamber indeed. The purpose is entirely " +
      "unclear, but it seems to be kind of ancestor worship or possibly " +
      "religious worship. The walls of the cave have been made smooth " +
      "with some unknown magic or technology. Various busts of people you " +
      "do not recognize have been carved out of the smoothed over walls. " +
      "There is no apparent pattern to their arrangement that you are " +
      "able to discern.");

   set_exits(([
      "north" : DIR + "/rooms/cliffs/cave/puzzle_chamber.c",
      "south" : DIR + "/rooms/cliffs/cave/cave_start.c"
   ]));

   add_item("bust", "The bust is expertly carved out of the smoothed " +
      "over walls. You do not know why the bust was made or who it " +
      "represents.");
   add_item("busts", "The busts have been carved out of the smoothed " +
      "over walls. No names are provided, nor do you recognize any of " +
      "them. Who they are and why they are memorialized are lost to " +
      "history.");
}

