inherit "/std/monster";
inherit "/std/modules/m_block_exits";
inherit "/std/modules/m_triggers";

void setup(void) {
   set_name("bob");
   set_gender("male");
   add_id("master", "guildmaster");
   set_short("Bob, the Fighter's Guildmaster");
   set_long("Bob is the leader of the Fighter's Guild. He is gray-haired, " +
      "but this does not by any means indicate weakness. After all, to " +
      "stay the leader you probably need to be pretty good at what you do.");
   set_race("human");
   set_level(15);
   add_block("north");

   if (clone_num() != 0) {
      set_actions(40, ({
         "say Surely you seek the path of a fighter!",
         "smile", "emote waves his sword around a bit while whistling.", 
       }));
   }

   add_pattern("%s smiles.", "smile $1");
}

int do_block(object who) {
   if (who->guild_member("fighter")) {
      return 0;
   }
   this_object()->respond("say Sorry. You need to be a member of the " +
      "fighters guild to enter.");
   return 1;
}
