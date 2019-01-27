#include "../../domain.h"

inherit DIR + "/lib/murder_hobo";

void setup(void) {
   set_race("dwarf");
   set_name("fighter");
   set_short("A fighter");
   set_long("The fighter is the party's tank and ultimate " +
      "killing machine.");

   equip_murder_hobo(({
      NOKICLIFFS_ARMORS_DIR + "/chain_mail.c",
      NOKICLIFFS_WEAPONS_DIR + "/claymore.c"
   }));
}
