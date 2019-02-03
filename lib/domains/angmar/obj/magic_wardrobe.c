#include "../domain.h"

inherit "/std/object";
inherit "/std/modules/m_openable";

void setup(void) {
   set_id("wardrobe");
   add_id("magic wardrobe");
   set_short("A magic wardrobe");
   set_long("It can take you to Fairyland if you enter it.");
   set_gettable(0);
   set_open_state(0);

   add_action("enter_wardrobe_cmd", "enter");
}

int enter_wardrobe_cmd(string str) {
   if (empty_str(str) || !is_id(str)) {
      return 0;
   }

   if (!query_open_state()) {
      this_player()->simple_action("$N $vtry to enter the closed wardrobe.");
      return 1;
   }

   this_player()->simple_action("$N $venter the magic wardrobe.");
   write("You feel weightless for a moment.");
   this_player()->move(FAIRYLAND_ROOMS + "/road1.c");
   this_player()->do_look(this_player()->query_environment());
   this_player()->simple_action("$N $vfall out of the sky and $vhit the ground in a cloud of dust.");

   return 1;
}