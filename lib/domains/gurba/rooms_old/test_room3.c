inherit ROOM;

void setup(void) {
   set_brief("%^RED%^Test_room3%^RESET%^");
   set_long("You shouldn't be able to get in here without using some " +
      "dirty wizard tricks.");

   set_exits(([
      "south" : "/domains/gurba/test_room1"
   ]));

   set_objects(([
      "/domains/gurba/objects/test_door#south" : ( { "south", "test_north"}),
   ]));
}
