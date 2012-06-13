inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("The tunnel slopes steeply down a hole here.");

   add_exit("west","/domains/2.4.5/rooms/tunnel23.c");
   add_exit("down","/domains/2.4.5/rooms/tunnel25.c");
}
