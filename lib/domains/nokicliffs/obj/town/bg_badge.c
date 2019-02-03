#include "../../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("bank guard badge");
   add_id("guard badge");
   add_id("badge");
   set_short("A bank guard badge");
   set_long("A shiny bank guard badge. There are only two ways to get one.");
   set_gettable(1);
   set_weight(1);
   set_value(1);
}
