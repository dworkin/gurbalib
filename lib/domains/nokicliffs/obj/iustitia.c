#include "../domain.h"

inherit "/std/object";
inherit DIR + "/lib/balance_check";

void setup(void) {
   set_gettable(0);
   set_id("iustitia");
   add_id("statue");
   set_short("A statue of Iustitia");
   set_long("This is a statue has been chiseled out of green granite. " +
      "The It has been shaped in the image of a female human wearing " +
      "an elegant robe. Her face is obscured because she is shown as " +
      "wearing a blindfold. In her right hand there is a scale with two " +
      "cups for balancing. In her left hand she holds an unsheathed " +
      "long sword with double edges.");
   set_weight(5000);
   set_value(0);
}

private void find_balance(object *balanced) {
   int i, dim;

   for (i = 0, dim = sizeof(balanced); i < dim; i++) {
      balanced[i]->destruct();
   }
}

void outside_message(string str) {
   string who;
   object player, law_shard, chaos_shard;
   object *inv, *balanced;
   int i, dim, is_balanced;

   str = ANSI_D->strip_colors(str);

   if (sscanf(str, "%s enters.", who) == 1) {
      player = this_object()->query_environment()->present(who);
      balanced = balance_check(player);
      is_balanced = sizeof(balanced) == 2;
   }
   if (!this_player()->is_completed_quest(NOKICLIFFS_SHARD_QUEST) &&
      is_balanced) {
      this_object()->query_environment()->tell_room(this_player(),
         "Iustitia shimmers with " +
         "balance as " + this_player()->query_Name() +
         " brings the shards of " +
         "law and chaos in her presence.");
      write("Iustitia shimmers with balance as you deliver the shards of " +
         "law and chaos to her.");
      write("You have completed the Quest for Balance. Congratulations, " +
         "champion.");
      this_player()->add_completed_quest(NOKICLIFFS_SHARD_QUEST);
      this_player()->increase_expr(NOKICLIFFS_SHARD_QUEST_XP_REWARD);
      find_balance(balanced);
      return;
   }
   if (is_balanced) {
      write("You have already brought balance to the realms. " +
         "But Iustitia accepts your gift of balance all the same.");
      find_balance(balanced);
   }
}
