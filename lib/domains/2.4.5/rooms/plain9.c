inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("A large open plain");
   set_long("A large open plain.  There is a river to the east and " +
      "some kind of building to the west.");

   add_exit("north","/domains/2.4.5/rooms/plain13.c");
   add_exit("south","/domains/2.4.5/rooms/ruin.c");
   add_exit("west","/domains/2.4.5/rooms/plain6.c");

   set_objects (([
      "/domains/2.4.5/monsters/frog.c": 1,
   ]));
}
