inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("A small storage room");
   set_long("you are in a small and dusty storage room.  You can see the " +
      "shop through the opening to the east.");

   add_exit("east","/domains/2.4.5/rooms/shop.c");
}
