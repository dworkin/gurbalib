#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("The small road outside an inn");
   set_long("You are on a small road outside the Laughing Horse Inn. " +
      "Laughter and clinking from glasses can be heard from the east. " +
      "The road continues north and south.");

   add_exit("north", FAIRYLAND_ROOMS + "/road3.c");
   add_exit("south", FAIRYLAND_ROOMS + "/road1.c");
   add_exit("east", FAIRYLAND_ROOMS + "/inn.c");

   add_item("road", "The road seems wellworn. As it should, seeing as how it is the main road.");
   add_item("inn", "You can see people laughing and drinking inside.");
   add_item("east", "To the east, you see the Laughing Horse Inn.");
   add_item("laughter", "It sounds like someone is BLASTED in there.");
   add_item("clinking", "Cheers! Stop listening, and join them.");

   add_action("listen_cmd", "listen");
}

int listen_cmd(string str) {
   this_player()->simple_action("$N $vhear the sounds of a bar in full swing coming " +
      "from the Laughing Horse Inn to the east.");
}