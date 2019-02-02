#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";
inherit DIR + "/lib/simple_block";

#define INTERVAL 15
static int count;
static string *acts;

void monster_died(void) {
   object automaton;

   automaton = this_object()->query_environment()->present("automaton");
   if (automaton && !automaton->is_inert()) {
      TELL_ROOM(this_object(), "The area glows with necromantic fury.");
      TELL_ROOM(this_object(), "The animated automaton melts into the void.");
      automaton->destruct();
   }
}

void bring_frankenstein_to_life(object brain, object automaton) {
   brain->destruct();
   automaton->destruct();

   respond("say It's alive! It's ALIVE!");
   respond("emote cackles megalomaniacally.");

   automaton = clone_object(DIR + "/monsters/doomspire/animated_automaton");
   automaton->move(this_object()->query_environment());
   automaton->setup();
}

private void gives(string str) {
   string who, what;
   object brain, automaton;

   if (sscanf(str, "%s gives the %s to you.", who, what) != 2) {
      return;
   }

   if (what == "brain") {
      brain = this_object()->present("brain");
      automaton = this_object()->query_environment()->present("automaton");

      if (!brain || !automaton || !automaton->is_inert()) {
         respond("say I'll find another use later. " +
            "But I always have a use for brains.");
         brain->destruct();

         return;
      }

      respond("emote puts the brain in the inert automaton.");
      respond("emote chants and weaves a necromantic spell.");
      call_out("bring_frankenstein_to_life", 4, brain, automaton);
   }
}

void outside_message(string str) {
   if (is_fighting()) {
      return;
   }

   gives(ANSI_D->strip_colors(str));
}

void do_extra_actions(void) {
   object ob;

   if (++count >= INTERVAL) {
      if (!is_fighting()) {
         ob = this_object()->query_environment()->present("automaton");
         if (ob && !ob->is_inert()) {
            return;
         }
         respond(random_element(acts));
         count = 0;
      }
   }
}

void setup(void) {
   set_name("necromancer");
   set_gender("male");
   set_short("A necromancer");
   set_long("The necromancer has animated many, many monsters so " +
      "far. He aspires to be like Angmar, the greatest necromancer " +
      "all time and place.");
   set_race("human");
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE * 3);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE * 5);
   add_block("up");

   acts = ({
      "say When you die, I'll make the most of most of you.",
      "emote cackles maniacally.",
      "say I need a brain to experiment with. Say, do you have any friends?"
   });
}
