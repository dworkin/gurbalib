#include "../../../domain.h"
inherit ROOM;

void setup(void) {
   set_brief("%^BLUE%^Fighters Guild Locker Rooms%^RESET%^");
   set_long("There are a bunch of lockers here.  Hey there is yours, to " +
      "the east.");

   set_exits(([
      "south" : DIR + "/guilds/fighter/rooms/main",
      "east" : "#go_locker",
   ]));

   add_room_command("locker","go_locker");
}

void go_locker(string str) {
   string locker;
   object obj;

   locker = DIR + "/data/lockers/" + this_player()->query_name();

   if (file_exists(locker + ".o")) {
/* XXX Need to do this...
     if (obj = find_object(locker)) {
         obj->save_me();
         obj->destruct();
      }
*/

      obj = clone_object(DIR + "/guilds/fighter/rooms/locker.c");

      if (!obj) {
         write("Error: Lockers are messed up.  Please talk to an admin.");
         return;
      }

      obj->setup();
      obj->set_player_name(this_player()->query_name());
      obj->restore_me();

      if (!obj) {
         write("Error: Your locker is nessed up.  Please talk to an admin.");
         return;
      }
   } else {
      obj = clone_object(DIR + "/guilds/fighter/rooms/locker.c");
      obj->setup();
      obj->set_player_name(this_player()->query_name());
      obj->save_me();
   }

/* XXX Need to add this to other moves like summon/goto */
   this_object()->event("body_leave", this_player());

   tell_room(this_player(), this_player()->query_Name() + " leaves east.\n");
   this_player()->move(obj);
   obj->tell_room(this_player(), this_player()->query_Name() + " enters.\n");
   this_player()->do_look(0);
}
