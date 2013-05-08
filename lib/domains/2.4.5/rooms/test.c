#include "../domain.h"

inherit "/std/room";

string east_door_open, name;
int a, amiga_present, amiga_power;


void setup(void) {
   add_area("2.4.5");

   set_short("Computer room");

   add_exit("east","/domains/2.4.5/rooms/rum2.c");
   add_action("sesam", "sesam");
   add_action("power", "power");

   set_objects (([
      DIR + "/obj/jacket.c": 1,
   ]));
}

string query_long() {
   string str;

   str = "You are in an old computer room.";
   if (amiga_present) {
      if (amiga_power) {
         str += "  A powered amiga is here.\n";
      } else {
         str += "  An amiga is here.\n";
      }
   }
   return str;
}

/* XXX Need to work on exits, computer and a bunch of other stuff. */

int sesam(string str) {
   if (amiga_present) {
      write("The amiga is already here!\n");
   } else {
      write("An amiga materialises!\n");
      amiga_present = 1;
      add_action("power", "power");
   }
   return 1;
}

int power(string str) {
   if (!amiga_present) {
      return 0;
   }
   if (amiga_power) {
      write("The screen dims.\n");
      amiga_power = 0;
      return 1;
   }
   write("The screen lights up.\n");
   amiga_power = 1;
   return 1;
}
