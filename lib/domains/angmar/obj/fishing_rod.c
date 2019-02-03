#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("fishing rod");
   add_id("rod");
   set_short("A fishing rod");
   set_long("Maybe you should fish and try your luck?");
   set_gettable(1);
   set_value(50);
   set_weight(1);

   add_action("fish_cmd", "fish");
}

int fish_cmd(string str) {
   str = this_player()->query_environment()->fish(this_player());

   if (empty_str(str)) {
     this_player()->simple_action("$N $vwant to try $p luck at fishing.");
   } else {
     this_player()->simple_action(str);
   }

   return 1;
}
