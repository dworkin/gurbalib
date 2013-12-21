#include "../domain.h"

inherit "/std/board";

void setup(void) {
   set_id("board");
   set_adj("message", "large");
   set_board_id("main");
}

string query_short(void) {
   return "The General message board [" + query_message_count() +
      " msgs]";
}

string query_long(void) {
   return query_message_list(this_player()->query_name()) +
      "Commands: post, read #, delete num\n";
}
