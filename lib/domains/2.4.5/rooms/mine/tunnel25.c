inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("The tunnel slopes steeply up here.");

   add_exit("north","/domains/2.4.5/rooms/tunnel26.c");
   add_exit("up","/domains/2.4.5/rooms/tunnel24.c");
}
