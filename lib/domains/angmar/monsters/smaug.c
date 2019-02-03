#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("smaug");
   set_race("dragon");
   set_adj("large ferocious");
   add_ids("large ferocious red dragon", "ferocious red dragon", "red dragon", "dragon");
   set_short("A large ferocious red dragon");
   set_long("A huge dragon. His name is Smaug and is rumoured to be the last. "+
            "of his kind. When you see him you really hope so. He looks like " +
            "he usually eat folks like you whole, and that his intent is to "+
            "prove it to you rather soon. He gives you a gaze that could "+
            "melt stone. Fumes come out of his nostrils in a way that "+
            "makes you feel that this dragon is sure of himself. He has NO " +
            "thoughts about losing a battle. His scars make you realize why. "+
            "The feeling his gaze inflicts in you gives you an insight in the "+
            "term \"premonition\".");
   set_level(30);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", BASE_OFFENSE * 8);
   set_skill("combat/defense", BASE_DEFENSE * 10);

   set_spell_chance(30);
   set_spell_damage(5);
   set_spell_message("Smaug bathes $t with some fire breath.");
}

private void add_treasure(string id, string str) {
   object obj;

   obj = this_object()->query_environment()->present(id);
   if (!obj) {
      obj = clone_object(str);
      obj->setup();
      obj->move(this_object()->query_environment());
   }
}

void monster_died(void) {
   object chainmail, ring;

   add_treasure("mithril chain mail", DIR + "/obj/armors/mithril_chain_mail.c");
   add_treasure("platinum ring", DIR + "/obj/quest_rings/platinum_ring.c");

   if (killer) {
      killer->simple_action("Smaug's treasure is before $N \b.");
   }
}