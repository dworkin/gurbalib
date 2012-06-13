inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("A small room");
   set_long("A small room with rough cut walls.");

   add_exit("south","/domains/2.4.5/rooms/tunnel5.c");

   set_objects (([
      "/domains/2.4.5/monster/hobgoblin.c": 1,
   ]));
}
