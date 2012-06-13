inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Deep forest");
   set_long("You are in the deep forest.");

   add_exit("north","/domains/2.4.5/rooms/forest3.c");
   add_exit("south","/domains/2.4.5/rooms/forest7.c");
   add_exit("east","/domains/2.4.5/rooms/forest6.c");
   add_exit("west","/domains/2.4.5/rooms/forest5.c");
}
