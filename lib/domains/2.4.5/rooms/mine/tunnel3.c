inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Hole");
   set_long("There is a big hole here, and some kind of iron rings in " +
      "the wall.  It should be possible to pass the hole.");

   add_exit("north","/domains/2.4.5/rooms/tunnel4.c");
   add_exit("south","/domains/2.4.5/rooms/tunnel2.c");
}

// XXX Add bit about rope to climb down...
