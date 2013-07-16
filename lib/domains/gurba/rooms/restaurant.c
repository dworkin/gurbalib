#include "../domain.h"

inherit "/std/room";

void setup(void) {
   set_short("Chez Mario");
   set_long("This is no five star restaurant, but it is indeed a nice " +
      "eating establishment, with a personal and charming touch to it. " +
      "The room has six tables, a small stage, and a bar with a door " +
      "behind it. The owner, Mario, is speeding around cleaning tables, " +
      "humming rapidly some piece of music and having a cigarette at the " +
      "same time.");

   set_exits(([
      "south" : DIR + "/rooms/border_south3",
      "north" : DIR + "/rooms/restaurant2",
   ]));

   add_item("tables", "table", "Each of the six wooden tables has four " +
      "chairs, and is clad in a big red'n'white checkered tablecloth.");
   add_item("bar", "At the opposite side of the entrance is a bar, " +
      "rising one and a half meters. In front of the bar are five " +
      "wooden barstools. Behind the bar are several shelves of beverages.");
   add_item("stage", "A small stage is at the west wall, just big " +
      "enough to hold a band of four.");
   add_item("tablecloth", "cloth", "It seems like any other tablecloth");
   add_item("stools", "stool", "barstool", "barstools",
      "Tall typical barstools.");
}
