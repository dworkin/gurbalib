#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town shop");
   set_long("You are in the Noki Town shop. " +
      "It is a cozy little general store. The locals " +
      "use it mostly for hanging out with each other, "+
      "which you are welcomed to do. That said, " +
      "you are in a shop, " +
      "sometimes things are bought and sold. " + 
      "Type 'list' to find out what's for sale today.");
   set_exits(([ "east" : DIR + "/rooms/town/square_middle.c" ]));
   set_objects(NOKICLIFFS_TOWN_SHOP_KEEPER,
      NOKICLIFFS_TOWN_SHOP_REGULAR);
}

