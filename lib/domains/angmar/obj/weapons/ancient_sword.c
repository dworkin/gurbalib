#include "../../domain.h"

inherit "/std/weapons/sword";

void setup(void) {
   ::setup();
   add_id("ancient sword");
   set_short("An ancient sword");
   set_long("This sword has the nicks and scrapes of a well-used blade. Although the "+
	   "hilt has been replaced several times, the blade is as keen and sharp " +
	   "as they day it was first ready for battle.");

   set_combat_stats(5, 20, 5);
}
