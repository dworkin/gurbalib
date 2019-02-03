#include "../../domain.h"

inherit "/std/object";

string query_key_code(void) {
   return "auxd";
}

void setup(void) {
   set_id("key");
   set_adj("big");
   set_short("A big key");
   set_long("The big key looks like it should unlock a strong door.");
   set_gettable(1);
   set_value(1);
   set_weight(1);
}
