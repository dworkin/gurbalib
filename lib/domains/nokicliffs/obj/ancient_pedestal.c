#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_gettable(0);
   set_id("pedestal");
   add_adj("ancient");
   set_short("An ancient pedestal of the Ancient One");
   set_long("This is not yet implemented. " +
      "Upon this ancient pedestal belongs " +
      "the blade of the ancient one.");
   set_weight(5000);
   set_value(0);
}

void outside_message(string str) {
   str = ANSI_D->strip_colors(str);
}
