#include "../../domain.h"

inherit DIR + "/lib/room";
inherit "/std/modules/m_block_exits";

void setup(void) {
   ::setup();

   set_short("At the bottom of the Noki Cliffs");
   set_long("You are the bottom of the Noki Cliffs " +
      "which rise high over head and disappear into the "+
      "cloud. If you are careful you can climb up the "+
      "cliffs from here. A mountain path snakes off to "+
      "the west from here.");
   set_exits(([
      "up" : DIR + "/rooms/cliffs/ledge.c",
      "west" : DIR + "/rooms/cliffs/path.c"
   ]));
   add_block("up");
}

int do_block(object who) {
   if (who->present("climbing gear")) {
      write("Fortunately you have some climbing gear that allows you to go.");
      return 0;
   }
   write("You need some climbing gear first.");
   return 1;
}

