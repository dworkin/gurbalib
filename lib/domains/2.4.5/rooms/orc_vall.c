inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The orc valley");
   set_long("You are in the orc valley.  This place is inhabited by orcs.  " +
      "There is a fortress to the north, with many signs of orcs.");
   add_exit("north","/domains/2.4.5/rooms/fortress.c");
   add_exit("east","/domains/2.4.5/rooms/slope.c");

   set_objects (([
      "/domains/2.4.5/monsters/orc.c": 1,
   ]));
}
