#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town bank");
   set_long("You are in the Noki Town bank. " +
      "This is a fairly secure place. The vault " +
      "room where clients' money is kept is to " +
      "the east and it is even more secure. You " +
      "get back to the town square by going west.");

   set_exits(([
         "east" : DIR + "/rooms/town/bank_vault_room.c",
         "west" : DIR + "/rooms/town/square_south.c"
      ]));
}

