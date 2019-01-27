#include "../../domain.h"

inherit "/std/room";
inherit "/std/modules/m_block_exits";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("The Laughing Horse Inn");
   set_long("You are in the Laughing Horse Inn. " +
      "It is always very well stocked. " +
      "You cannot leave with the drinks you buy " +
      "here.");

   add_exit("west", FAIRYLAND_ROOMS + "/road2.c");

   set_objects(
         DIR + "/monsters/bar_tender.c",
         DIR + "/monsters/drunkard.c"
   );

   add_block("west");
}

int do_block(object who) {
   object *inv;
   int i, sz;

   inv = who->query_inventory();
   sz = sizeof(inv);
   for (i = 0; i < sz; i++) {
      if (inv[i]->is_laughing_horse_in_drink()) {
         who->message("You can't leave with the drinks you buy here.");
         return 1;
      }
   }

   return 0;
}
