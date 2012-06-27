inherit M_GUILD_MASTER;

void setup(void) {
   set_guild("fighter");
   set_name("bob");
   set_proper_name("Bob");
   set_gender("male");
   add_id("master", "guildmaster");
   set_in_room_desc("Bob, the Fighter's Guildmaster");
   set_long("Bob is the leader of the Fighter's Guild. He is gray-haired, " +
      "but this does not by any means indicate weakness. After all, to " +
      "stay the leader you probably need to be pretty good at what you do.");
   set_race("human");
   set_level(15);
   add_block("north");
   if (clone_num() != 0) {
      set_actions(80, ( {
	    "say Surely you seek the path of a fighter!",
	    "say All you have to do is say 'join'.",
	    "say Say 'join' to become a fighter.",
	    "smile", "emote waves his sword around a bit while whistling.", 
       } ));
   }
   add_pattern("%s says: Join", "call join_guild $1");
   add_pattern("%s says: Leave", "call leave_guild $1");
   add_pattern("%s smiles.", "smile $1");
}

int can_join(object player) {
   return 1;
}

void do_join(object player) {
   this_player()->respond("say Welcome to the Fighter's Guild, " +
      player->query_name());
   this_player()->respond("smile");
   this_player()->respond("bow " + player->query_name());
}

void do_reject(object player) {
   this_player()->respond("say Sorry, you're too puny to join.");
}

int can_leave(object player) {
   return 1;
}

void do_leave(object player) {
   this_player()->respond("say Sorry to see you go.");
   this_player()->respond("sigh");
   this_player()->respond("say A great loss for this guild.");
}

void do_keep(object player) {
   this_player()->respond("say You're too valuable an asset to this guild, " +
      "so I can't let you go.");
}
