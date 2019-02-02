#include "../domain.h"

inherit "/std/monster";

#define INTERVAL 10
static string *acts;
static int count;

void do_extra_actions(void) {
   count++;
   if (count >= INTERVAL) {
      count = 0;
      if (!is_fighting()) {
         if (random(2)) {
            respond(random_element(acts));
         }
      }
   }
}

void add_act(string act) {
   if (nilp(acts)) {
      acts = ({ });
   }
   acts += ({ act });
}

void set_acts(string *new_acts) {
   if (nilp(new_acts) || sizeof(new_acts) == 0) {
      new_acts = ({ });
   }
   acts = new_acts;
}
   
string *get_default_acts(void) {
   string *default_acts;
   default_acts = allocate(5);
   default_acts[0] = "emote flutters about in the sun.";
   default_acts[1] = "emote zips around the clearing.";
   default_acts[2] = "emote sings an ancient faerie tune.";
   default_acts[3] = "emote buzzes a few blades of grass.";
   default_acts[4] = "emote is in her happy place.";
   return default_acts;
}

void create(void) {
   ::create();
   set_gender("female");
   set_race("faerie");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE);
   set_acts(get_default_acts());
}

