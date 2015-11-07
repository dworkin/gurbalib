#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("Ye old saloon");
   set_long("A large wooden bar stretches across the back of the room.  " +
      "Other than that the room is currently pretty empty.  There are " +
      "a bunch of chairs pushed up against tables scattered about the room.");

   set_exits(([
      "west" : DIR + "/rooms/infront_saloon.c",
   ]));

   set_objects(DIR + "/obj/piano.c");

   add_action("do_play", "play");
}

int do_play(string str) {
   int x;

   if (!this_object()->present("piano")) {
      return 0;
   }

   if (str == "piano") {
      x = random(5);
      switch(x) {
         case 0:
            write("You play a little ditty.");
            this_environment()->tell_room(this_player(), 
               this_player()->query_Name() + " plays a little ditty.");
            break;
         case 1:
            write("You stroke the keys with love.");
            this_environment()->tell_room(this_player(), 
               this_player()->query_Name() + " plays a sweet little number.");
            break;
         case 2:
            write("You bring it home.");
            this_environment()->tell_room(this_player(), 
               this_player()->query_Name() + " stuns you with their " + 
               "rendition of Chopin.");
            break;
         default:
            write("You work the keyboard like it was your best friend.");
            this_environment()->tell_room(this_player(), 
               this_player()->query_Name() + " plays an old country song.");
            break;
      }
      return 1;
   }
   return 0;
}

