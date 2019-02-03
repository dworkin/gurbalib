#include "../../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("silver ring");
   set_adj("silver");
   add_ids("ring", "trlock2");
   set_short("A silver ring");
   set_long("A beautiful silver ring. It is very skillfully made, with " +
     "some writings in it. Although you don't understand the language, " +
     "you can decipher the name Angmar.");
   set_slot("finger");
   set_value(0);
   set_gettable(1);
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The silver ring falls into the Void, gone forever.");
   this_object()->destruct();
   return 1;
}
