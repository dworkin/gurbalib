#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The local prison");
   set_long("You are in the local prison.  There are no exits.");

   add_room_command("quit","quit");
}

int quit(string str) {
   write("You can't leave.\n");
   return 1;
}
