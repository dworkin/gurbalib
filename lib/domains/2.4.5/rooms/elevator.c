#include "../domain.h"

inherit "/std/room";

int location, destination;
string open;

void set_floor(int x) {
   destination = x;

   tell_room(this_object(), "The elevator starts moving.\n");

   switch (location) {
      case 0:
         open = "closed";
         remove_exit("east");
         break;
      case 1:
         open = "open";
         remove_exit("east");
         add_exit("east", DIR + "/rooms/wiz_hall.c");
         break;
      case 2:
         open = "open";
         remove_exit("east");
         add_exit("east", DIR + "/rooms/church.c");
         break;
      case 3:
         remove_exit("east");
         add_exit("east", DIR + "/rooms/attic.c");
         open = "open";
         break;
   }
}

int query_location() {
   return location;
}

void setup(void) {
   add_area("2.4.5");

   set_short("Elevator");

   location = 1;
   set_floor(1);
   add_exit("north", DIR + "/rooms/vill_shore.c");
   add_action("press_button", "press");
   add_action("press_button", "push");
}

string query_long() {
   string str;

   str = "You are in the elevator.  On the wall are three buttons, " +
      "numbered 1 to 3.\nCurrently the number " + destination + 
      " button is lit.  The door to the east is " + open + "\n";

   return str;
}

/* XXX Need to do the door, button and stuff.... */

int press_button(string str) {
   object elev;

   if (str == "1") {
      write("You press button 1.\n");
      this_object()->tell_room(this_player(), this_player()->query_Name() +
         " presses button 1.\n");
      set_floor(1);

   } else if (str == "2") {
      write("You press button 2.\n");
      this_object()->tell_room(this_player(), this_player()->query_Name() +
         " presses button 2.\n");
      set_floor(2);

   } else if (str == "3") {
      write("You press button 3.\n");
      this_object()->tell_room(this_player(), this_player()->query_Name() +
         " presses button 3.\n");
      set_floor(3);

   } else {
      write("Which button do you want to press? (1, 2, 3)?\n");
   }
   return 1;
}

