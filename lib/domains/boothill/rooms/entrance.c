#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("Outside town");
   set_long("A small dirt road leads north to a small frontier town.");

   set_exits(([
      "north" : DIR + "/rooms/welcome.c", 
      "west" : DIR + "/rooms/outside_town.c",
   ]));
}
