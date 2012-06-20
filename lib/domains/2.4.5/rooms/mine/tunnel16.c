inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Tunnel");
   set_long("In the tunnel into the mines.");

   add_exit("north","/domains/2.4.5/rooms/tunnel17.c");
   add_exit("west","/domains/2.4.5/rooms/tunnel15.c");

   set_objects (([
      "/domains/2.4.5/monsters/dwarf.c": 1,
   ]));
}
