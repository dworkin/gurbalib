#include "../domain.h"

inherit "/std/object";

/* This object tests the various functions of a basic object to make
   sure it is upto snuff. */
void setup(void) {
   set_id("object");
   set_adj("small");
   set_short("A test object");
   set_long("A pretty boring grey rock.");
   set_gettable(1);
   set_weight(1);
   /* This isn't a special rock... */
   set_value(0);
}

string query_long() {
}
