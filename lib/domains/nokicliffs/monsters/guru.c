#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

#define INTERVAL 10
static int count;
static string *emotes;
static string *available_emotes;

void setup(void) {
   set_name("swami");
   add_id("guru");
   set_gender("male");
   set_short("Swami the Noki Guru");
   set_long("Swami the Noki Guru lives atop the Noki Cliffs. " +
      "It would be most unwise to attack him. He sits in a " +
      "perpetual lotus position.");
   set_race("human");
   set_level(99);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 500);
   set_skill("combat/defense", 500);
}

private string guru_emote(void) {
   int i, dim;

   if (nilp(emotes)) {
      emotes = ({"pensive", "meditate", "think", "ponder", "wonder"});
   }
   if (nilp(available_emotes)) {
      available_emotes = ({"say Om."});
      for (i = 0, dim = sizeof(emotes); i < dim; i++) {
         if (EMOTE_D->is_emote(emotes[i])) {
            available_emotes += ({emotes[i]});
         }
      }
   }
   dim = sizeof(available_emotes);
   return available_emotes[random(dim)];
}

void do_extra_actions(void) {
   count = count + 1;
   if (count >= INTERVAL) {
      respond(guru_emote());
      count = 0;
   }
}

void outside_message(string str) {
   string who, what, where;
   object shell, player, beads;

   str = ANSI_D->strip_colors(str);
   str = lowercase(str);

   if (sscanf(str, "%s gives %s to you.", who, what) == 2) {
      player = this_environment()->present(who);
      shell = this_object()->present("seashell");

      if (shell) {
         destruct_object(shell);
         /*
            if (!player->is_completed_quest("Guru Seashell")) {
            player->add_completed_quest("Guru Seashell");
            player->increase_expr(200);
            player->message("Well done, champion.\n");
            }
          */
         beads = clone_object(NOKICLIFFS_DIMENSIONAL_BEADS);
         beads->set_owner_name(player);
         beads->update_short();
         if (beads->move(player)) {
            player->message("Swami gives you a string of beads.\n");
         } else {
            player->message("Swami tried to give you a string of beads, " +
               "but you are already carrying too much.");
         }
      }
   }
}
