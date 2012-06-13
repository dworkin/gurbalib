inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The orc fortress");
   set_long("THis is the local strong point of the orcs.  There is an " +
      "entrance to a small room to the north.");

   set_objects (([
      "/domains/2.4.5/monster/orc.c": 1,
      "/domains/2.4.5/monster/orc.c": 1,
   ]));

}

// XXX make it so orcs do not let you pass... but have exits...
