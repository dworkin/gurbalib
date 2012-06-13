inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("Tunnel fork.");

   add_exit("south","/domains/2.4.5/rooms/tunnel19.c");
   add_exit("east","/domains/2.4.5/rooms/tunnel23.c");
   add_exit("west","/domains/2.4.5/rooms/tunnel21.c");
}
