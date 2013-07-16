inherit "/std/room";

void setup(void) {
   add_area("required");

   set_short("A large open field");
   set_long("You are in a large open field.  To the north you see a large " +
      "dead tree with some sort of sign on it.  To the east you see more " +
      "prairie.  To the west you see the ancient city of gurba.  To the " +
      "south you see a large forest.");

   set_exits(([
      "north" : "/domains/newbie/rooms/tree", 
      "south" : "/domains/2.4.5/rooms/forest1", 
      "east" : "/domains/boothill/rooms/outside_town",
      "west" : "/domains/gurba/rooms/gate_east",
   ]));
}
