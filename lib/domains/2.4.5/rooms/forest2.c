inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("In a forest");
   set_long("You are in a big forest.");

   add_exit("east","/domains/2.4.5/rooms/clearing.c");
   add_exit("west","/domains/2.4.5/rooms/slope.c");

  set_objects (([
   "/domains/2.4.5/monsters/troll.c": 1,
  ]));
}
