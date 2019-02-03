#include "../../domain.h"

inherit "/std/object";
inherit "/std/modules/m_readable";

void setup(void) {
   set_id("sign");
   set_short("A sign at the entrance to Darkwood");
   set_long("It seems to have been here for quite a while.");
   set_message("The road is closed due to the many accidents " +
               "caused by the creatures in the forest.");
   set_gettable(0);
}
