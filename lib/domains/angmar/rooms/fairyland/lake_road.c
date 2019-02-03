#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);
   set_short("By Great Lake");
   set_long("You are standing by Great Lake. You can hear the gulls crying.");

   add_exit("east", FAIRYLAND_ROOMS + "/by_lake.c");
   add_exit("west", FAIRYLAND_ROOMS + "/crossing.c");

   add_item("water", "The lake stretches out for a few miles.");
   add_item("lake", "The lake stretches out for a few miles.");
   add_item("Great Lake", "The lake stretches out for a few miles.");
   add_item("great lake", "The lake stretches out for a few miles.");
   add_item("sea", "You cannot see it. It must be behind the mountain.");
   add_item("gulls", "The gulls must have come from the sea nearby.");

   add_action("listen_cmd", "listen");
}

int listen_cmd(string str) {
   if (!empty_str(str) && (str == "gulls" || str == "to the gulls")) {
       this_player()->simple_action("$N $vlisten to the gulls cry.");
       return 1;
   }

   return 0;
}
