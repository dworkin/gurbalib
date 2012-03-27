inherit ROOM;

void setup(void) {
   add_area("newbie");

   set_brief("%^MAGENTA%^Outside the jail.%^RESET%^");
   set_long("You are on main street, infront of the town jail.  Main " +
      "runs north and south whilte the jail is to your east.");

   set_exits(([
      "north" : "/domains/boothill/rooms/boothill.c", 
      "south" : "/domains/boothill/rooms/infront_saloon.c", 
      "east" : "/domains/boothill/rooms/jail.c", 
   ]));
}
