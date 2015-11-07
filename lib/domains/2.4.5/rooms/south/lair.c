#include "../../domain.h"
inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The bottom of the well");
   set_long("You are standing at the bottom of the well.  " +
      "About thirty feet below the surface.  Bones lie strewn about in a " +
      "random fashion, many of them broken or shattered.  The only way out " +
      "is the way in, back up the ladder.");

   add_exit("up", DIR + "/rooms/south/sislnd17.c");

   set_objects(DIR + "/monsters/wyrm.c");
}
