inherit ROOM;

void setup(void) {
   set_brief("%^BLUE%^Test_room1%^RESET%^");
   set_long("A small and nondescript test room.");

   set_exits(([
      "east" : "/domains/gurba/town_square",
      "west" : "#What you think look like an exit is too small to " +
         "squeeze through.\n", 
      "north" : "/domains/gurba/test_room3"
   ]));

   set_objects(([
      "/domains/gurba/objects/rock": 1,
      "/domains/gurba/monsters/rat": 1,
      "/domains/gurba/objects/test_door#east": ( { "east", "town_square_west"}),
      "/domains/gurba/objects/test_door#north": ( { "north", "test_north"}),
   ]));
}
