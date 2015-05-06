#include "../../../domain.h"

inherit "/std/guild_book";

void setup(void) {
   set_id("book");
   set_long("This book is attached to a large chain which is " +
      "fastened to the wall.  It is titled, the definitive guide to the " +
      "fighters guild.");
   set_short("A sturdy book");

   set_message("Welcome to the fighters guild.  If you want to join our " +
      "guild type 'join'.  If you want to leave the guild type " +
      "'leave'.  The fighters guild is a prestigious group of, well " +
      "fighters.");

   set_guild("fighter");

   add_action("join_guild", "join");
   add_action("leave_guild", "leave");
}

int can_join(object player) {
   return 1;
}

int do_reject(object player) {
   write("The guild master tells you: Sorry, you're too puny to join.");
   return 1;
}

int do_join(object player) {
   write("The guild master tells you: Welcome to the Fighters Guild, " +
      player->query_name());
   return 1;
}

int can_leave(object player) {
   return 1;
}

int do_keep(object player) {
   write("The guild master says: You're too valuable an asset to this guild, " +
      "so I can't let you go.");
   return 1;
}

int do_leave(object who) {
   write("The guild master says: Sorry to see you go.");
   write("The guild master sighs.");
   write("The guild master says: A great loss for this guild.");
   return 1;
}

