#include "../domain.h"
inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The adventures guild");
   set_long("You have to come here when you want to advance your level.  " +
      "You can also buy points for a new level.  There is an opening to the " +
      "south, and some shimmering blue light in the doorway.  " +
      "There is also a small note nailed to the wall.");
   add_exit("north", DIR + "/rooms/vill_road2.c");
   add_exit("south", "/domains/required/rooms/bug_room.c");

   set_objects(DIR + "/obj/book.c");

   add_item("chain", "The chain is secured to the wall.\n");
   add_item("note", "If your looking for adventure, Retrieve the Orc " +
      "slayer from the evil orc shaman, and give it to Leo.");
}

/* If you look at the original, there was a bunch of stuff here for
   leveling up, however were doing it differently so does not apply.
   You may want to look at the old code for more info... XXX
*/
