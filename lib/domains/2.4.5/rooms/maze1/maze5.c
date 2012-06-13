inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("End of the maze");
   set_long("Congradulations you have done it.);

   add_exit("south","/domains/2.4.5/rooms/maze1/maze4.c");

   set_objects (([
      "/domains/2.4.5/obj/leather.c": 1,
   ]));

}
