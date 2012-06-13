inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("The tunnel splits up in a fork forward.");

   add_exit("north","/domains/2.4.5/rooms/tunnel17.c");
   add_exit("south","/domains/2.4.5/rooms/tunnel22.c");
}
