inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("The tunnel into the mines.");

   add_exit("north","/domains/2.4.5/rooms/tunnel19.c");
   add_exit("south","/domains/2.4.5/rooms/tunnel16.c");
   add_exit("west","/domains/2.4.5/rooms/tunnel18.c");
}
