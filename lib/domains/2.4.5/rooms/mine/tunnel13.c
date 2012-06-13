inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("End of the tunnel.");

   add_exit("south","/domains/2.4.5/rooms/tunnel12.c");
}
