#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("shard");
   add_id("lawshard");
   add_adj("lawful");
   set_short("A shard of law");
   set_long("A shard of lawfulness. It's purpose is not immediately " +
      "clear from just looking at it. Perhaps someone else knows and " +
      "has a use for it.");
   set_gettable(1);
   set_value(0);
   set_weight(1);
   add_bane("lawfulness");
}

