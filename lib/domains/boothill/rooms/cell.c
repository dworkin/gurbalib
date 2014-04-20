#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("boothill");

   set_short("A very small jail cell");
   set_long("There isn't a whole heck of a lot here.");

   set_exits(([
      "west" : DIR + "/rooms/jail.c", 
   ]));

}
