#include "../../../domain.h"
inherit ROOM;
inherit M_STORAGE;

void setup(void) {
   set_brief("%^BLUE%^Fighters Guild Locker Rooms%^RESET%^");
   set_long("There are a bunch of lockers here.  Hey there is yours, to " +
      " the east.");

   set_exits(([
      "south" : DIR + "/guilds/fighter/rooms/main",
   ]));
}

void go_locker {
   string locker;
   object obj;

   locker = REQDIR + "data/lockers/" + this_player()->query_name() + ".o";

   if (file_exists(locker)) {
      obj = find_object(locker);
      if (!obj) {
      }
   } else {
      obj = clone_object(REQDIR + "obj/locker.c");
      obj->set_player_name(this_player()->query_name());
      obj->save_me();
   }

   /* XXX Do move to obj.... here */
}
