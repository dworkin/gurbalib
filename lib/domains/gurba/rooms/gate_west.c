inherit ROOM;

void setup(void) {
   add_area("Gurba");
   add_area("GurbaOutdoor");
   add_area("BorderWalk");
   add_area("BorderWalkWest");

   set_brief("Western Gate of Gurba Town");
   set_long("You are at the western entrance to the town of Gurba. The " +
      "gate itself is a large, ancient arch of stone, connected on " +
      "either side to the tall, worn stone wall that marks the " +
      "perimeter of the town. The neat brick paving of the streets " +
      "transitions to a dirt road as it leads through the gate into the " +
      "lands beyond. To the east Market Street leads toward the town " +
      "square through one of the oldest districts of town, while to the " +
      "north and south Border Walk runs parallel to the wall.");

   set_exits(([
      "east" : "/domains/gurba/rooms/market4",
      "south" : "/domains/gurba/rooms/border_west4",
      "north" : "/domains/gurba/rooms/border_west5",
   ]));

   add_item("gate", "The ancient stonework of the gate is etched with " +
      "the inscription 'Scientia et Pertinacia.'  Beyond it the dirt " +
      "road leads toward what looks like a an open field.");
}
