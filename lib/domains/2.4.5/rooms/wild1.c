inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Wilderness");
   set_long("You are in the wilderness outside the village.  There is a big " +
      "forest to the west.");

   add_exit("east","/domains/2.4.5/rooms/hump.c");
   add_exit("west","/domains/2.4.5/rooms/forest1.c");
}
