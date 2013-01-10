#include "../../../domain.h"
inherit ROOM;

string player_name;
string *myitems;

void restore_me(void) {
   object obj;
   int i, max;

   if (!unguarded("restore_object", DIR + "/data/lockers/" +
      player_name + "/locker.o")) {
      write("Error while restoring " + DIR + "/data/lockers/" +
         player_name + "/locker.o");
      write("Please notify the administration.");
      return;
   }
   max = sizeof(myitems);
   for (i=0; i<max; i++) {
      obj = clone_object(myitems[i]);
      unguarded("restore_object", DIR + "/data/lockers/" + player_name + 
         "/" + i + ".o");
   }
   set_brief(capitalize(player_name) + "'s locker room");
}

void save_me(void) {
   int x, y, max;
   object *objs;
   myitems = ({});

   unguarded("save_object", DIR + "/data/lockers/" + player_name + "/locker.o");

   objs = this_object()->query_inventory();
   if (objs) {
      max = sizeof(objs);
   } else {
      max = 0;
   }
   y = 0;
   for (x=0; x<max; x++) {
      if (objs[x]->is_living()) {
      } else {
         myitems[y] = objs[x]->base_name();
         unguarded("save_object", DIR + "/data/lockers/" + player_name + 
            "/" + y + ".o");
         y = y + 1;
      }
   }

   unguarded("save_object", DIR + "/data/lockers/" + player_name + "/locker.o");
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

/* On exit need to save_me and destroy this object... XXX */
