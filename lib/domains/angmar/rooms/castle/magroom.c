#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("Magic workroom");
   set_long("This seems to be a magic workroom. Many different " +
            "kinds of magical tools are scattered around the place.");

   add_exit("east", CASTLE_ROOMS + "/midstairs.c");
   add_exit("west", CASTLE_ROOMS + "/library.c");

   add_item("tools", "You can't determine the function of half of them.");
   add_item("magical tools", "You can't determine the function of half of them.");
   add_item("workroom", "It is obviously a place where magic is performed routinely.");

   set_objects(
         DIR + "/obj/cauldron/cauldron.c"
   );
}

