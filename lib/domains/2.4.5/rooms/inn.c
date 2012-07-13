#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Eastroad Inn");
   set_long("You are in the Eastroad Inn.  Here you can buy food to still " +
      "your hunder, but only a limited selection is available.");

   add_exit("east", DIR + "/rooms/eastroad5.c");
}

// XXX Need to add store stuff...
