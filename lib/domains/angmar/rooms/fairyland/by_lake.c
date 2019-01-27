#include "../../domain.h"

inherit "/std/room";
inherit "/std/modules/m_block_exits";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("By Great Lake");
   set_long("You are standing by Great Lake. You can hear the gulls crying. " +
      "If you go east, you will end up in a clump of reeds.");

   add_exit("east", FAIRYLAND_ROOMS + "/reeds.c");
   add_exit("west", FAIRYLAND_ROOMS + "/lake_road.c");

   add_item("water", "Great Lake, the lake where Smaug is said to drink.");
   add_item("cold water", "Great Lake, the lake where Smaug is said to drink.");
   add_item("lake", "Great Lake, the lake where Smaug is said to drink.");
   add_item("Great Lake", "Great Lake, where Smaug is said to drink.");
   add_item("great lake", "Great Lake, where Smaug is said to drink.");
   add_item("reeds", "You think you see something behind the reeds.");
   add_item("clump of reeds", "You think you see something behind the clump of reeds.");
   add_item("gulls", "They flit off in the distance, echoes of their cries in the air.");

   add_action("listen_cmd", "listen");

   add_block("east");
}

int do_block(object who) {
   object boots;

   boots = who->present("rubber boots");
   if (!boots || !boots->query_worn()) {
      who->simple_action("$N $vtry to go east but $vlack rubber boots to keep $p feet dry in the cold water.");
      return 1;
   }

   who->simple_action("$N $vtrudge east while wearing $p rubber boots to keep $p feet dry in the cold water.");
   return 0;
}

int listen_cmd(string str) {
   if (!empty_str(str) && (str == "gulls" || str == "to the gulls")) {
      this_player()->simple_action("$N $vlisten to the gulls' cries in the distance.");
      return 1;
   }

   return 0;
}
