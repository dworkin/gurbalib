inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("%^MAGENTA%^Welcome to town.%^RESET%^");
   set_long("A large sign streaches across the road.  It reads: \"Welcome " +
      "to town\".  The road north, bends to the west here.");

   set_exits(([
      "north" : "/domains/boothill/rooms/infront_saloon.c",
      "south" : "/domains/boothill/rooms/entrance.c", 
   ]));
}
