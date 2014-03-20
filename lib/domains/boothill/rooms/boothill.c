#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("Boothill");
   set_long("If your not sure what boothill is, now you know, its a " +
      "cemetery just outside of town.  There are a bunch of cheap " +
      "graves here.  With Odd looking tombstones.  There is also a " +
      "freshly dug hole, just waiting for the towns next victim.  You see a " +
      "small path to the east here behind the bushes.");

   set_exits(([
      "south" : DIR + "/rooms/infront_jail.c", 
      "east" : DIR + "/rooms/mntpath.c", 
      "down" : DIR + "/rooms/hole.c",
   ]));

   set_objects(DIR + "/obj/tombstone.c");

  add_item("hole", "It's actually a fairly deep hole.  " +
     "It's hard to see into it from up here.");

}

