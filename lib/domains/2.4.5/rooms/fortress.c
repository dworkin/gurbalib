inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The orc fortress");
   set_long("THis is the local strong point of the orcs.  There is an " +
      "entrance to a small room to the north.");

   set_objects (([
      "/domains/2.4.5/monsters/orc.c": 2,
   ]));

   add_exit("north","/domains/2.4.5/rooms/orc_treasure.c");
   add_exit("south","/domains/2.4.5/rooms/orc_vall.c");

}
