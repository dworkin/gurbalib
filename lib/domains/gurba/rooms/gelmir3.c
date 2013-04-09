#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GelmirRoad");
   add_area("GurbaOutdoor");

   set_short("Gelmir Road");
   set_long("This section of Gelmir Road is dominated by a bunch of " +
      "formidable-looking individuals wearing armor and carrying " +
      "weapons.  Most of them seem to be coming and going from the " +
      "Fighter's Guild to the north, whose large tiled dome towers " +
      "over the surrounding buildings.  The entrance is large and " +
      "ornate, and wide enough for several people to come and go at " +
      "once.  Gelmir Road heads west from here towards the town " +
      "square, and in the other direction towards the eastern gate " +
      "of the town.");

   set_exits(([
      "east" : DIR + "/rooms/gelmir4",
      "west" : DIR + "/rooms/gelmir2",
      "north" : DIR + "/guilds/fighter/rooms/entrance",
   ]));
}
