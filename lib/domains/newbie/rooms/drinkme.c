inherit ROOM;

void setup(void) {
   add_area("newbie");

   set_brief("Waiting Area");
   set_long("You are in a small tunnel.  This room looks like a small " +
      "waiting area.  You hear loud noises to the north.");

   set_exits(([
      "north" : "/domains/newbie/rooms/equipment", 
      "south" : "/domains/newbie/rooms/quest",
   ]));

   set_objects(([
      "/domains/newbie/obj/table":1,
   ]));
}
