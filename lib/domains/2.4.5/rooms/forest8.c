inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Deep forest");
   set_long("You are in the deep forest.");

   add_exit("south","/domains/2.4.5/rooms/forest9.c");
   add_exit("east","/domains/2.4.5/rooms/forest5.c");
}
