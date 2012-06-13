inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Lair of the Giant");
   set_long("There are mountains all around you.");

   add_exit("east","/domains/2.4.5/rooms/giant_path.c");
   add_exit("west","/domains/2.4.5/rooms/giant_conf.c");

   set_objects (([
      "/domains/2.4.5/monsters/giant.c": 1,
   ]));
}
