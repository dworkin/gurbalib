#include "../domain.h"

inherit obj "/std/object";

void setup() {
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

void outside_message(string str) {
	string who;
	object player, law_shard, chaos_shard;
	object *inv;
	int i, dim, player_has_law_shard, player_has_chaos_shard;

	str = ANSI_D->strip_colors(str);
	
	if (sscanf(str, "%s enters.", who) == 1) {
		player = this_object()->query_environment()->present(who);
		if (player) {
			inv = player->query_inventory();
			for (i = 0, dim = sizeof(inv); i < dim; i++) {
				if (inv[i]->is_id("lawshard")) {
					player_has_law_shard = 1;
					law_shard = inv[i];
				}
				if (inv[i]->is_id("chaosshard")) {
					player_has_chaos_shard = 1;
					chaos_shard = inv[i];
				}
			}
		}
	}
	if (!this_player()->is_quest_completed(NOKICLIFFS_SHARD_QUEST) &&
			player_has_law_shard && player_has_chaos_shard) {
		this_object()->query_environment()->tell_room(this_player(),
			"Iustitia shimmers with " +
			"balance as " + this_player()->query_Name() +
			" brings the shards of " +
			"law and chaos in her presence.");
		write("Iustitia shimmers with balance you deliver the shards of " + 
			"law and chaos to her.");
		this_player()->add_completed_quest(NOKICLIFFS_SHARD_QUEST);
		this_player()->add_expr(NOKICLIFFS_SHARD_QUEST_XP_REWARD);
		destruct_object(law_shard);
		destruct_object(chaos_shard);
		write("You have completed the Quest for Balance. Congratulations, " + 
			"champion.");
	}
}

