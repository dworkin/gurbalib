inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Village road");
   set_long("A long road going east through the village.  The road narrows " +
      "to a track to the west.  There is an alley to the north and the south");

   add_exit("north","/domains/2.4.5/rooms/yard.c");
   add_exit("south","/domains/2.4.5/rooms/narr_alley.c");
   add_exit("east","/domains/2.4.5/rooms/vill_road2.c");
   add_exit("west","/domains/2.4.5/rooms/vill_track.c");
}
