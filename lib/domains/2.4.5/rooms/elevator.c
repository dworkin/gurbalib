#include "../domain.h"
inherit ROOM;
int location, destination;

void set_floor(int x) {
   destination = x;
   switch (location) {
      case 1:
         break;
      case 2:
         break;
      case 3:
         break;
   }
}

void setup(void) {
   add_area("2.4.5");

   set_brief("Elevator");

   location = 1;
   set_floor(1);
   add_exit("north", DIR + "/rooms/vill_shore.c");
}

string query_long() {
   string str;

   str = "You are in the elevator.  On the wall are three buttons, " +
      "numbered 1 to 3.\nCurrently the number " + destination + 
      " button is lit.";

   return str;
}

/* XXX Need to do the door, button and stuff.... */
