inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("A slope");
   set_long("The forest gets light here, and slopes down to the west.);

   add_exit("south","/domains/2.4.5/rooms/orc_vall.c");
   add_exit("east","/domains/2.4.5/rooms/forest2.c");
   add_exit("west","/domains/2.4.5/rooms/forest3.c");
}
