#include "../domain.h"

inherit "/std/container";

/* XXX although we can't currently put coins into containers... */
void after_move(object player, object what) {
   what->move(NOKICLIFFS_VOID);
   what->destruct();
   player->message("Thank you for your generous donation. The " +
      (what->is_money() ? "coins" : ("value of the " + what->query_id()) +
      " will be used to fund our operations."));
}

void setup(void) {
   set_id("box");
   set_adj("donation");
   set_short("A donation box");
   set_long("A donation box. You can put things in it " +
      "show your appreciation and to keep the place " +
      "beautiful.");
}
