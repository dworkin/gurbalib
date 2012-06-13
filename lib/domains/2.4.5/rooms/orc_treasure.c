inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The orc treasury");
   set_long("You are in the orc treasury.  It is normally heavily guarded.");

   add_exit("south","/domains/2.4.5/rooms/fortress.c");

   set_objects (([
      "/domains/2.4.5/monsters/orc_slayer.c": 1,
      "/domains/2.4.5/monsters/orc_shayman.c": 1,
   ]));
}

// XXX add staff and sword on the monsters???
