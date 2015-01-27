#include "../../../domain.h"

inherit "/std/room";

void setup(void) {
   set_short("%^BLUE%^Fighters Guild%^RESET%^");
   set_long("This is the main room of the Fighters Guild. To the north " +
      "is the storage room.");

   set_exits(([
      "south" : DIR + "/guilds/fighter/rooms/entrance", 
      "north" : DIR + "/guilds/fighter/rooms/storage",
   ]));

   set_objects(DIR + "/guilds/fighter/objects/fighter_board");
}
