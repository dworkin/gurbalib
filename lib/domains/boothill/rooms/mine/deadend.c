#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("mine");

   set_short("A dead end");
   set_long("Who ever was digging this mine hit this passage and just gave " +
      "up.  The walls are roughly cut and ends abruptly.");

   set_exits(([
      "west" : DIR + "/rooms/mine/passages.c",
   ]));

   set_objects(DIR + "/monsters/spider.c");
}

