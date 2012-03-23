inherit ROOM;

void setup(void) {
   set_brief("%^BLUE%^Fighters Guild%^RESET%^");
   set_long("This is the main room of the Fighters Guild. To the north " +
      "is the storage room.");

   set_exits(([
      "south" : "/domains/gurba/guilds/fighter/rooms/entrance", 
      "north" : "/domains/gurba/guilds/fighter/rooms/storage",
   ]));

   set_objects(([
      "/domains/gurba/guilds/fighter/objects/fighter_board":1,
   ]));
}
