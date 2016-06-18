#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("The Hall of Balance");
   set_long("You are standing in the fabled Hall of Balance. " +
      "If you thought the outside was the epitome of balance, think again. " +
      "This room is the true epitome of balance. The grand columns, the " +
      "granite tiled floor, everything. It is so much balance you feel a " +
      "bit dizzy.");

   set_exits(([
      "west": DIR + "/rooms/hall_of_balance/hall_of_balance_start.c"
   ]));

   set_objects(DIR + "/obj/iustitia.c");
}

