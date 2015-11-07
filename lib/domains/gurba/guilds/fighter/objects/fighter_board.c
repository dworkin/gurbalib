inherit "/std/board";

void setup(void) {
   if (clone_num() == 0) {
      return;
   }
   if (!query_environment()) {
      return;
   }
   set_id("board");
   set_adj("message", "large");
   set_board_id("fighter");
}

string query_short(void) {
   return "The Fighters board of discussion [" +
      query_message_count() + " msgs]";
}

string query_long(void) {
   return query_message_list(this_player()->query_name()) +
      "Commands: post, read #, delete num\n";
}

