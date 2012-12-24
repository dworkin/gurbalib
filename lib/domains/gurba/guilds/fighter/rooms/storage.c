#include "../../../domain.h"
inherit ROOM;

void setup(void) {
   set_brief("%^BLUE%^Fighters Guild Locker Rooms%^RESET%^");
   set_long("There are a bunch of lockers here.  Hey there is yours, to " +
      " the east.");

   set_exits(([
      "south" : DIR + "/guilds/fighter/rooms/main",
      "east" : "#go_locker",
   ]));
}

void go_locker(void) {
   string locker;
   object obj;

   locker = DIR + "data/lockers/" + this_player()->query_name() + ".o";

   if (file_exists(locker)) {
      obj = find_object(locker);
      if (!obj) {
      }
   } else {
      obj = clone_object(DIR + "obj/locker.c");
      obj->set_player_name(this_player()->query_name());
      obj->save_me();
   }

   this_object()->event("body_leave", this_player());
   tell_room(this_player(), this_player()->query_Name() + " leaves east.\n");
   obj->event("body_enter", this_player());
   obj->tell_room(this_player(), this_player()->query_Name() + " enters.\n");
}
