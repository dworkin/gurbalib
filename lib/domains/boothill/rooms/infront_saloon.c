inherit ROOM;

void setup(void) {
   add_area("newbie");

   set_brief("%^MAGENTA%^Welcome to town.%^RESET%^");
   set_long("You are on main street, infront of a large saloon, to your " +
      "east.");

   set_exits(([
      "north" : "/domains/boothill/rooms/infront_store.c", 
      "south" : "/domains/boothill/rooms/entrance.c", 
      "east" : "/domains/boothill/rooms/saloon.c", 
   ]));
}
