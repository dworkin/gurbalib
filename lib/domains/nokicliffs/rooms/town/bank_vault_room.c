#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town bank");
   set_long("You are in the Noki Town bank's vault.");
   set_exits(([ "west" : DIR + "/rooms/town/bank.c" ]));
   set_objects(
      DIR + "/monsters/town/bank_guard.c",
      DIR + "/obj/town/vault.c"
   );   
}

