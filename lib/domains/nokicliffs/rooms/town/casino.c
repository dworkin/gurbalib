#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town casino");
   set_long("You are at Noki Town's casino. A grand " +
      "staircase leads up to the hotel lobby. The " +
      "public bath is north from here. Many of the " +
      "villagers are here, as well as a goodly number " +
      "of transients, playing the most famous game in " +
      "Noki Town, the one-armed bandit.");

   set_exits(([
      "up" : DIR + "/rooms/town/hotel_lobby.c",
      "north" : DIR + "/rooms/town/public_bath.c"
   ]));

   set_objects(NOKICLIFFS_TOWN_ONE_ARMED_BANDIT);

   add_item("grand staircase", "It sure is grand. It was " +
      "built by Noki Town's finest carpenters, builders, and " +
      "artisans.");
   add_item("staircase", "It's a grand staircase built by Noki " +
      "Town's finest carpenters, builders, and artisans.");
   add_item("villagers", "The villagers are enjoying the casino.");
   add_item("transients", "The transients are enjoying the casino.");
}
