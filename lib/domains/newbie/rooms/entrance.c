inherit ROOM;
#define DIR "/domains/newbie"

void setup(void) {
   add_area("newbie");

   set_brief("Inside a tunnel");
   set_long("You are in a small tunnel.  It was a tight squeeze to get in " +
      "here.");

   set_exits(([
      "out" : DIR + "/rooms/tree", 
      "south" : DIR + "/rooms/equipment",
   ]));
}
