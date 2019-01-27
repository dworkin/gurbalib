#include "../domain.h"

inherit "/std/modules/m_block_exits";

int do_block(object who) {
   if (who->present("climbing gear")) {
      write("Fortunately you have some climbing gear that allows you to go.");
      return 0;
   }
   write("You need some climbing gear first.");
   return 1;
}
