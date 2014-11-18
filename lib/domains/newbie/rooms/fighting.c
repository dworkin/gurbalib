#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("newbie");

   set_short("The newbie arena");
   set_long("You are in a small tunnel.  It was a tight squeeze to get in " +
      "here.  There is a large flower in the middle of the room.");

   add_item("flower", "A Large flower sits in the middle of the room.  " +
      "Perhaps you should pick it.");

   add_action("do_pick", "pick");

   set_exits(([
      "north" : DIR + "/rooms/equipment", 
      "south" : DIR + "/rooms/drinkme",
   ]));
}

int do_pick(string arg) {
   if (arg == "flower") {
      object obj;

      write("As you reach for the flower, a giant bunny rabbit appears, " +
         "blocking your way.\n");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() +
         " reaches for the flower in the center of the room.\n" +
         "All of a sudden a giant bunny rabbit appears blocking their path.\n");

      obj = clone_object(DIR + "/monsters/bunny.c");
      obj->setup();
      obj->move(this_player()->query_environment());
      obj->attack(this_player());
      return 1;
   } else {
      return 0;
   }
}
