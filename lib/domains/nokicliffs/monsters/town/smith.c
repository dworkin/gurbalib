#include "../../domain.h"

inherit "/std/monster";

int busy_right_now;

int query_busy_right_now(void) {
   return busy_right_now;
}

void work_done(object affixable, object target, int coins, object client) {
   target->add_affix(affixable->query_id());
   affixable->destruct();
   respond("emote smiles proudly.");
   respond("say There we go. All done.");
   respond("give " + target->query_id() + " to " + client->query_name());
   busy_right_now = FALSE;
}

void clink2(object affixable, object target, int coins, object client) {
   TELL_ROOM(this_object(), "*clink* *clink* *clink*");
   respond("emote examines his work carefully.");
   call_out("work_done", 3, affixable, target, coins, client);
}

void clink1(object affixable, object target, int coins, object client) {
   client->simple_action("The smith hammers on $p stuff with godly " +
      "might.", client);
   TELL_ROOM(this_object(), "*clink* *clink* *clink*");
   call_out("clink2", 2, affixable, target, coins, client);
}

void add_affix_to_target(object affixable, object target,
      int coins, object client) {
   busy_right_now = TRUE;
   client->add_money("ducat", -coins);
   affixable->move(this_object());
   target->move(this_object());
   client->simple_action("$N $voffer $p payment and $p stuff to the smith.",
      client);
   client->simple_action("The smith takes $p payment and $p stuff " +
      "and gets to work. He pulls out a giant hammer...", client);
   call_out("clink1", 2, affixable, target, coins, client);
}

void remove_work_done(string affixable, object target,
      int coins, object client) {
   target->remove_affix(affixable);
   respond("emote smiles proudly.");
   respond("say There we go. All done.");
   respond("give " + target->query_id() + " to " + client->query_name());
   busy_right_now = FALSE;
}

void clunk2(string affixable, object target, int coins, object client) {
   TELL_ROOM(this_object(), "*clunk* *clunk* *clunk*");
   respond("emote examines his work carefully.");
   call_out("remove_work_done", 3, affixable, target, coins, client);
}

void clunk1(string affixable, object target, int coins, object client) {
   client->simple_action("The smith hammers on $p stuff with godly " +
                         "might.", client);
   TELL_ROOM(this_object(), "*clunk* *clunk* *clunk*");
   call_out("clunk2", 2, affixable, target, coins, client);
}

void remove_affix_from_target(string affixable, object target,
      int coins, object client) {
   busy_right_now = TRUE;
   client->add_money("ducat", -coins);
   target->move(this_object());
   client->simple_action("$N $voffer $p payment and $p stuff to the smith.",
      client);
   client->simple_action("The smith takes $p payment and $p your stuff " +
      "and gets to work. He pulls out a giant hammer...", client);
   call_out("clunk1", 2, affixable, target, coins, client);
}

void setup(void) {
   set_name("smith");
   add_id("noki town smith");
   set_gender("male");
   set_short("The Noki Town smith");
   set_long("The Noki Town smith is friendly but gets straight " +
      "to the point. He is very skilled at his trade and is " +
      "always looking to improve his skills.");
   set_race("half-giant");
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE);
   busy_right_now = FALSE;
}
