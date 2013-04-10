inherit "/std/monster";
inherit "/std/modules/m_block_exits";
inherit "/std/modules/m_triggers";
inherit "/std/modules/m_actions";

string guild;

void set_guild(string new_guild) {
   guild = new_guild;
}

string query_guild(void) {
   return (guild);
}

int do_block(object who) {
   if (who->guild_member(guild)) {
      return 0;
   }
   this_object()->respond("say Sorry. You need to be a member of this guild " +
      "to enter.");
   return 1;
}

void do_dub(object who) {
   who->set_title("$N the newest member.");
}

void join_guild(string who) {
   object player;

   player = USER_D->find_player(who);
   if (!player)
      return;

   if (player->guild_member(guild)) {
      this_player()->respond("say You're already a member.");
      return;
   }

   if (this_object()->can_join(player)) {
      player->join_guild(guild);
      this_object()->do_join(player);
   } else {
      this_object()->do_reject(player);
      return;
   }

   do_dub(player);

   CHANNEL_D->chan_join(query_guild(), player);
   CHANNEL_D->event_player_join(( {
	    player->query_name(), GUILD_D->query_guild_title(query_guild())
	 }
      ));
}

void leave_guild(string who) {
   object player;

   player = USER_D->find_player(who);
   if (!player)
      return;

   if (!player->guild_member(guild)) {
      this_player()->respond("say Why do you want to leave, when you're " +
         "not a member?");
      return;
   }

   if (this_object()->can_leave(player)) {
      player->leave_guild(guild);
      this_object()->do_leave(player);
      CHANNEL_D->chan_leave(query_guild(), player);
      player->set_title("$N the guildless.");

   } else {
      this_object()->do_keep(player);
   }
}
