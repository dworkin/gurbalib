inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("%^MAGENTA%^Outside the general store.%^RESET%^");
   set_long("You are on main street, infront of the general store.  Main " +
      "runs north and south while the general store is to your west.  " +
      "The road, if you can call it that, seems paticularily muddy here.");

   set_exits(([
      "north" : "/domains/boothill/rooms/infront_jail.c", 
      "south" : "/domains/boothill/rooms/infront_saloon.c", 
      "west" : "/domains/boothill/rooms/general_store.c", 
   ]));
}
