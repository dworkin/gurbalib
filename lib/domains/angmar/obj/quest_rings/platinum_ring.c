#include "../../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("platinum ring");
   set_adj("platinum");
   add_ids("ring", "trlock1");
   set_short("A platinum ring");
   set_long("A pretty platinum ring. It has some inscriptions, but the " +
      "words seems like gibberish, except for the name Angmar.");
   set_slot("finger");
   set_value(0);
   set_gettable(1);
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The platinum ring falls into the Void, gone forever.");
   this_object()->destruct();
   return 1;
}