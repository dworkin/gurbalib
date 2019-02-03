#include "../../domain.h"

inherit DIR + "/lib/room";
inherit "/std/modules/m_block_exits";
inherit DIR + "/lib/balance_check";

void setup(void) {
   set_short("The Hall of Balance, in a pocket dimension");
   set_long("You are standing in a small pocket dimension containing the " +
      "fabled Hall of Balance. As you gaze upon the facade of the Hall of " +
      "Balance it is impossible to miss how utterly balanced is everything " +
      "about it; everything from the sizes to shapes to colors to " +
      "measurements of every conceivable kind. This is the epitome of " +
      "balance and you know that only those who are prepared to bring " +
      "this kind of balance to the realms shall be allowed to enter the " +
      "Hall of Balance. If you are not ready yet you can always 'leave' the " +
      "pocket dimension.");

   set_exits(([
      "east" : DIR + "/rooms/hall_of_balance/hall.c",
      "leave" : NOKICLIFFS_BASE_CAMP
   ]));

   add_block("east");
}

int do_block(object player) {
   if (sizeof(balance_check(player)) != 2) {
      write("You have not found balance yet, hero.");
      return 1;
   }

   return 0;
}

