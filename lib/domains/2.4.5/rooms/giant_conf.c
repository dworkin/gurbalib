inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Giants conference of human bashing");
   set_long("You are at the yearly conference of human bashing, " +
      "organized by the giants");

   add_exit("east","/domains/2.4.5/rooms/giant_lair.c");

  set_objects (([
      "/domains/2.4.5/monsters/fire_giant.c": 1,
      "/domains/2.4.5/monsters/frost_giant.c": 1,
      "/domains/2.4.5/monsters/stone_giant.c": 1,
   ]));

}
