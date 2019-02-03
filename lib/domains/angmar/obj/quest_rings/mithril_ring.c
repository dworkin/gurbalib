#include "../../domain.h"

inherit "/std/armor";

void setup(void) {
   set_id("mithril ring");
   set_adj("mithril");
   add_ids("ring", "trlock3");
   set_short("A mithril ring");
   set_long("A very beautiful ring made of the rare mithril metal. " +
           "The inscriptions in it are in a language unknown to you, but you " +
           "can read the name Angmar.");
   set_slot("finger");
   set_value(0);
   set_gettable(1);
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
     "The mithril ring falls into the Void, gone forever.");
   this_object()->destruct();
   return 1;
}
