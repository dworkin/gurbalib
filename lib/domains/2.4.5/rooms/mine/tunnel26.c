inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("In the tunnel.");

   add_exit("north","/domains/2.4.5/rooms/tunnel27.c");
   add_exit("south","/domains/2.4.5/rooms/tunnel25.c");
   add_exit("east","/domains/2.4.5/rooms/tunnel28.c");
}
