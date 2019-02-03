#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);

   set_short("Angmar's castle");
   set_long("This is the castle of Angmar. " +
      "Angmar, the necromancer, has not been seen in " +
      "this world for hundreds of years. Rumours say that " +
      "he is long dead. His castle, however, still stands " +
      "here as a monument of Evil, and it is quite possible " +
      "that the ghastly creatures conjured by Angmar still " +
      "lurks inside, guarding his immense riches.");

   add_exit("north", "/domains/2.4.5/rooms/crop.c");
   add_exit("south", CASTLE_ROOMS + "/inside.c");
}