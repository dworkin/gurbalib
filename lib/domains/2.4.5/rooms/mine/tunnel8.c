#include "../../domain.h"
inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Shaft");
   set_long("In a shaft going straight down.");

   add_exit("up", DIR + "/rooms/mine/tunnel3.c");
   add_exit("down", DIR + "/rooms/mine/tunnel9.c");
}
