inherit ROOM;

void setup(void) {
   add_area("Gurba");
   add_area("BorderWalk");
   add_area("BorderWalkNorth");
   add_area("GurbaOutdoor");

   set_brief("Intersection of Border Walk/Borland Avenue");
   set_long("Here, the long rectangular Border Walk crosses the end of " +
      "Borland Avenue, a small but well-maintained residental district " +
      "of the town, which leads to the south from here. The sounds of " +
      "children playing can be heard. The Border Walk continues to the " +
      "east and west.");

   set_exits(([
      "east" : "/domains/gurba/rooms/border_north6",
      "west" : "/domains/gurba/rooms/border_north5",
      "south" : "/domains/gurba/rooms/borland3",
   ]));
}
