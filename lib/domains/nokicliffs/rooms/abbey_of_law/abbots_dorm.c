#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("The Abbot of the Abbey of Law's dorm.");
   set_long("You are in the abbot's dorm. To describe this room as " +
      "'spartan' is a terrific understatement. There is an incredibly " +
      "uncomfortable looking bed and a small desk with nothing but " +
      "centuries of dust upon it. There is nothing else in the room " +
      "except for a stained glass window which shows the abbey's " +
      "patron saint.");

   set_exits(([
      "south" : DIR + "/rooms/abbey_of_law/outside_chapel.c"
   ]));

   set_objects(DIR + "/monsters/abbot.c");
}
