inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Small yard");
   set_long("A small yard surrounded by houses.");

   add_exit("south","/domains/2.4.5/rooms/vill_road1.c");
   add_exit("east","/domains/2.4.5/rooms/pub2.c");

   set_objects (([
      "/domains/2.4.5/monsters/beggar.c": 1,
      "/domains/2.4.5/obj/knife.c": 1,
   ]));
}
