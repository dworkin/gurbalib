#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("On a rock ledge");
   set_long("You You step onto a small rock ledge on Misty Mountain. " +
       "Judging by the bits and pieces of a burned out fire here, " +
       "it seems that someone has been living on the ledge.");

   add_exit("west", FAIRYLAND_ROOMS + "/mountain.c");

   add_item("mountain", "The mountain has formed a natural ledge here.");
   add_item("misty mountain", "The mountain has formed a natural ledge here.");
   add_item("pieces", "There are a few ashes around a chunk of charred wood.");
   add_item("bits", "There are a few ashes around a chunk of charred wood.");
   add_item("ashes", "You feel them, and they seem to be relatively recent.");
   add_item("wood", "Strangely enough, the wood seems hardly burned. Magic, perhaps...");
   add_item("ledge", "The ledge seems very dangerous. Try not to fall off.");
   add_item("fire", "There are a few ashes around a chunk of charred wood.");

   set_objects(DIR + "/monsters/oracle.c");

   add_action("search_ashes_cmd", "search");
}

int search_ashes_cmd(string str) {
   if (empty_str(str) || str != "ashes") {
      return 0;
   }

   this_player()->simple_action("$N $vsift through the ashes, but $vfind nothing.");
   return 1;
}
