#include "../../../domain.h"
inherit ROOM;

string player_name;

void restore_me(void) {
   if (!unguarded("restore_object", DIR + "/data/lockers/" +
      player_name + ".o")) {
      write("Error while restoring " + DIR + "/data/lockers/" +
         player_name + ".o");
      write("Please notify the administration.");
      return;
   }
   set_brief(capitalize(player_name) + "'s locker room");
}

void save_me(void) {
   unguarded("save_object", DIR + "/data/lockers/" + player_name + ".o");
}

void set_player_name(string str) {
   player_name = str;
   set_brief(capitalize(player_name) + "'s locker room");
}

void setup(void) {
   set_brief(" An unknown locker room");
   set_long("You can store your stuff here.");

   set_exits(([
      "west" : DIR + "/guilds/fighter/rooms/storage.c",
   ]));
}
