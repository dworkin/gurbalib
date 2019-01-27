#include "../domain.h"

inherit NOKICLIFFS_ROOT;

int do_eat(void) {
   if (is_spoiled()) {
      write("It's spoiled. Yuck!");
   } else {
      this_player()->targeted_action("$N $veat some " +
         "fae beet root and $vturn " +
         "%^B_RED%^bright red%^RESET%^ for " +
         "a moment.", this_object());
   }
   this_object()->destruct();
   return 1;
}

void handle_properly_dried(void) {
   object env;

   env = this_object()->query_environment();
   if (env->is_living()) {
      env->message("The beet root has properly dried. " +
         "It is now edible. But you know what they " +
         "say about eating fae food, right?");
   }
   set_eatable(1);
   set_value(10);
   set_short("A properly dried bit of fae beet root");
   set_long("This is a piece of properly dried fae " +
      "beet root. It looks delicious.");
}

void setup(void) {
   ::setup();
   set_id("fae beet root");
   add_ids("beet root", "root");
   set_short("A fresh bit of fae beet root");
   set_long("This is a fresh bit of fae beet " +
      "root. It has not been properly dried. " +
      "Once properly dried, it is said that " +
      "fae beet roots are delicious to eat.");
}
