#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("amulet");
   add_ids("small amulet");
   set_adj("small");
   set_short("A small amulet");
   set_long("It is a beautiful stone in a necklace.");
   set_gettable(1);
   set_value(100);
   set_weight(1);
}
