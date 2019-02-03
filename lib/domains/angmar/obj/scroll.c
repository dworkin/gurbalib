#include "../domain.h"

inherit "/std/object";
inherit "/std/modules/m_readable";

void setup(void) {
   set_id("magic scroll");
   add_id("scroll");
   set_short("A magic scroll");
   set_long("According to the ancient runes this scroll can revive petrified people.");
   set_value(40);
   set_weight(1);
   set_gettable(1);
   set_message("#revive");
}

void revive(void) {
   object statue;
   string str;

   statue = this_player()->query_environment()->present("stone statue");
   str = "$N $vread a magic scroll which then vanishes.";

   if (!statue) {
      str += " And nothing else happens.";
      this_player()->simple_action(str);
      return;
   }

   str += " And something happens...";
   this_player()->simple_action(str);
   statue->revive();
}

int do_read(object who) {
   revive();
   this_object()->destruct();

   return 1;
}
