inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("A large open plain");
   set_long("A large open plain, There is some kind of building to the east.");

   add_exit("north","/domains/2.4.5/rooms/plain6.c");
   add_exit("south","/domains/2.4.5/rooms/plain2.c");
   add_exit("east","/domains/2.4.5/rooms/ruin.c");
   add_exit("west","/domains/2.4.5/rooms/plain7.c");
}
