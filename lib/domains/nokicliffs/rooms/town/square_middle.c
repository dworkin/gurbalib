#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_short("Noki Town central square");
   set_long("You are in the middle of the Noki Town " +
      "square. A large fountain of crisp, clear mountain " +
      "melt water is here. There are some coins in the " +
      "fountain that people have thrown in upon making " +
      "wishes. It would not be nice of you to take them. " +
      "Villagers are milling about, going about their " +
      "business. You can go north to the northern end " +
      "of the town square, south to the southern end " +
      "of it; or you can go east to the chapel or " +
      "west to the shop.");
   set_exits(([
      "north" : DIR + "/rooms/town/square_north.c",
      "south" : DIR + "/rooms/town/square_south.c",
      "east" : DIR + "/rooms/town/chapel.c",
      "west" : DIR + "/rooms/town/shop.c"
   ]));
}

