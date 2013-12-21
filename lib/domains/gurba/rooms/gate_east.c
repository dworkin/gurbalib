#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GurbaOutdoor");
   add_area("BorderWalk");
   add_area("BorderWalkEast");

   set_short("Eastern Gate of Gurba Town");
   set_long("You are at the eastern entrance to the town of Gurba.  " +
      "The gate itself is a large, ancient arch of stone, connected on " +
      "either side to the tall, worn stone wall that marks the perimeter " +
      "of the town.  The neat brick paving of the streets transitions " +
      "to a dirt road as it leads through the gate into the lands " +
      "beyond.  To the east you see a large open field.  To the west " +
      "Gelmir Road leads toward the town square.  Boarder Walk runs  " +
      "north and south.");

   set_exits(([
      "north" : DIR + "/rooms/border_east5",
      "south" : DIR + "/rooms/border_east4",
      "east" : STARTING_ROOM,
      "west" : DIR + "/rooms/gelmir4",
   ]));

   add_item("gate", "The ancient stonework of the gate is etched with the " +
      "inscription 'Scientia et Pertinacia.'  Beyond it the dirt road " +
      "leads toward a large open field.");
}
