inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("A large open plain");
   set_long("A large open plain, extending to the north and south.");

   add_exit("north","/domains/2.4.5/rooms/plain3.c");
   add_exit("south","/domains/2.4.5/rooms/plain1.c");
   add_exit("east","/domains/2.4.5/rooms/plain4.c");
   add_exit("west","/domains/2.4.5/rooms/plain5.c");
}
