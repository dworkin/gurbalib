inherit ROOM;

void setup(void) {
   add_area("newbie");

   set_brief("Inside a tunnel");
   set_long("You are in a small tunnel.  It was a tight squeeze to get in " +
      "here.");

   set_exits(([
      "out" : "/domains/newbie/rooms/tree", 
      "south" : "/domains/newbie/rooms/equipment",
   ]));
}
