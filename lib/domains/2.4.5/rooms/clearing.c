inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Clearing");
   set_long("A small clearing.  There are trees all around you.  However, " +
      "the trees are sparse to the north.");

   add_exit("north","/domains/2.4.5/rooms/plain1.c");
   add_exit("east","/domains/2.4.5/rooms/forest1.c");
   add_exit("west","/domains/2.4.5/rooms/forest2.c");
}
