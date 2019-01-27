#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("candy");
   add_ids("taffy", "salt-water taffy");
   set_short("A piece of candy");
   set_long("It's a small piece of salt-water taffy.  There's a bit of dirt " +
      "and dust on the candy, but it looks edible enough.  It brings " +
      "you back a few years, to when you were a child, and loved candy.");
   set_eatable(1);
   set_gettable(1);
   set_value(2);
   set_weight(1);

   add_action("lick_candy_cmd", "lick");
}

int do_eat(void) {
   this_player()->simple_action("$N $vsink $p teeth into a piece of salt-water taffy, " +
      "which tastes delicious.");
   this_object()->destruct();
   return 1;
}

int lick_candy_cmd(string str) {
   if (!empty_str(str) && is_id(str)) {
      this_player()->simple_action("$N $vlick a small piece of salt-water taffy, " +
         "which dissolves on $p tongue and tastes delicious.");
      this_object()->destruct();
      return 1;
   }

   return 0;
}
