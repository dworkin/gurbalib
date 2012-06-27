inherit ROOM;
#define DIR "/domains/boothill"

void setup(void) {
   add_area("boothill");

   set_brief("Outside the jail");
   set_long("You are on main street, infront of the town jail.  Main " +
      "runs north and south while the jail is to your east.");

   set_exits(([
      "north" : DIR + "/rooms/boothill.c", 
      "south" : DIR + "/rooms/infront_saloon.c", 
      "east" : DIR + "/rooms/jail.c", 
   ]));
}
