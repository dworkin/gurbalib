inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Dead end");
   set_long("Another dead end.");

   add_exit("west","/domains/2.4.5/rooms/mine/tunnel28.c");

   set_objects (([
      "/domains/2.4.5/monsters/dragon.c": 1,
   ]));
}
