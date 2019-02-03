#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("Eagle's nest");
   set_long("You are on the top of Misty Mountain. It's very cold up here, although " +
      "the view of the fairyland below is terrific. There is an eagle's nest here.");

   add_exit("down", FAIRYLAND_ROOMS + "/mountain.c");

   add_item("nest", "The home of a few eaglets, which are mysteriously missing.");
   add_item("fairyland", "The expanse of land beneath you stretches out to the horizon.");
   add_item("mountain", "The mountain stretches below you. You can see a ledge and a door.");
   add_item("door", "You cannot tell if the door is open or closed.");
   add_item("ledge", "There is an indistinguishable figure on the ledge.");
   add_item("figure", "You can't make out the details. The figure is too far away.");

   set_objects(DIR + "/monsters/eagle.c");
}
