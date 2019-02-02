#include "../domain.h"

inherit "/std/object";
inherit "/std/modules/m_openable";

static int scroll_flag;

void setup(void) {
   set_id("box");
   add_id("small box");
   set_short("A small box");
   set_long("It is a small rusty box. It must have been very long in the water.");
   set_gettable(1);
   set_open_state(0);
   set_weight(1);
   set_value(0);

   scroll_flag = 0;
}

int do_open(object who) {
   int x;
   object scroll;

   x = ::do_open(who);

   if (x == 1 && scroll_flag == 0) {
      who->simple_action("As $N $vopen the box, something falls out of it to the ground.");
      scroll = clone_object(DIR + "/obj/scroll.c");
      scroll->setup();
      scroll->move(who->query_environment());
      scroll_flag = 1;
   }

   return x;
}
