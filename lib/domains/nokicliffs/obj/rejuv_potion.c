#include "../domain.h"

inherit "/std/object";
inherit NOKICLIFFS_HEALING_LIB;

void setup(void) {
   set_id("rejuvination potion");
   add_ids("potion");
   set_short("A rejuvination potion");
   set_long("The rejuvination potion is in a " +
      "small round glass bottle with a cork stopper. " +
      "The potion is a swirling thick lavender coloured " +
      "liquid, which is quite viscuous but drinkable. " +
      "You should only " +
      "drink this when you need full body, " +
      "mind, and endurance healing.");
   set_eatable(1);
   set_gettable(1);
   set_value(2);
   set_weight(1);
}

/* we won't stop you. */
int hp_needed(object patient) {
   return 1;
}

int mana_needed(object patient) {
   return 1;
}

int end_needed(object patient) {
   return 1;
}

int do_eat(void) {
   string str;
   object doc, patient;
   int    max_hp, max_mana, max_end;

   str = "$N $vdrink a potion of rejuvination " +
      "and $vlook like a new " + 
      this_player()->query_race() + ". " +
      "The potion itself disappears in a puff of " +
      "smoke.";
   doc = this_player();
   patient = this_player();
   max_hp = patient->query_max_hp();
   max_mana = patient->query_max_mana();
   max_end = patient->query_max_end();
   recover_hp(doc, patient, max_hp, nil);
   recover_mana(doc, patient, max_mana, nil);
   recover_end(doc, patient, max_end, str);
   this_object()->destruct();
}
