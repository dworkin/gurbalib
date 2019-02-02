#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

static string remember_name1;
static string remember_name2;
static string remember_name3;

void setup(void) {
   set_name("oracle");
   set_gender("female");
   set_race("Oracle");
   set_short("The all-wise oracle");
   add_ids("all-wise oracle", "wise oracle");
   set_adj("all-wise");
   set_long("He sits here alone, meditating over things incomprehensible " +
            "to ordinary people. If you have a problem, he might be able to " +
            "help you.");

   remember_name1 = "";
   remember_name2 = "";
   remember_name3 = "";
}

int has_rings(object player) {
   return player->present("trlock1") && player->present("trlock2") && player->present("trlock3");
}

int here_before(string str) {
   str = lowercase(str);

   return str == remember_name1 || str == remember_name2 || str == remember_name3;
}

void remember(string str) {
   remember_name3 = remember_name2;
   remember_name2 = remember_name1;
   remember_name1 = lowercase(str);
}

void forget(string str) {
      str = lowercase(str);

      if (str == remember_name3) {
         remember_name3 = "";
      }

      if (str == remember_name2) {
         remember_name2 = "";
      }

      if (str == remember_name1) {
         remember_name1 = "";
      }
}

void event_heart_beat(void) {
   object doomsgiver;

   doomsgiver = this_object()->present("doomsgiver");
   if (doomsgiver) {
      doomsgiver->destruct();
      this_object()->query_environment()->tell_room(this_object(),
         "The Oracle makes a magical gesture and her doomsgiver disappears.");
   }

   ::event_heart_beat();
}

string say_start(void) {
   return "%^GREEN%^The Oracle says:%^RESET%^ ";
}

void outside_message(string str) {
   string who, password, says;
   object doomsgiver, quester;

   if (is_fighting()) {
      return;
   }

   str = ANSI_D->strip_colors(str);

   if (sscanf(str, "%s gives the doomsgiver to you.", who) == 1) {
      str = lowercase(who);
      quester = this_object()->query_environment()->present(str);
      doomsgiver = this_object()->present("doomsgiver");
      if (!quester || !doomsgiver) {
         return;
      }
      password = call_other(CASTLE_ROOMS + "/treasury_entrance", "generate_password", quester);
      says = "Thank you, " + who + ". Now listen carefully. The password to the doors " +
            "changes all the time. It is '" + password + "' right now, but can change " +
            "any minute, so hurry! And good luck!";
      quester->simple_action(say_start() + says);
      return;
   }

   if (sscanf(str, "%s enters.\n", who) == 1) {
      str = lowercase(who);
      quester = this_object()->query_environment()->present(str);
      if (!quester || quester->is_completed_quest(ANGMAR_TREASURY_QUEST)) {
         return;
      }

      if (here_before(str)) {
         says = "Welcome again, " + who + ".";
         if (has_rings(quester)) {
            says += " Did you get the sword for me as you promised?";
         } else {
            says += " You need three special rings before I can help you.";
         }
         quester->simple_action(say_start() + says);
         return;
      }

      says = "Welcome, " + who + ".\nThe Oracle smiles.";
      if (has_rings(quester)) {
         says += "\n" + say_start() + "I see that you have found the three rings. " +
            "Looking for the password, eh?\n" +
            "The Oracles leans closer to $N \b.\n";
         if (quester->present("doomsgiver")) {
            says += say_start() + "If you give the famous sword Doomsgiver to me " +
                  "I can help you.";
         } else {
            says += say_start() + "If you could find the famous sword Doomsgiver and " +
            "give it to me, I might help you. It is said to be found somewhere " +
            "deep in the castle of Angmar, but beware! The legend also tells of " +
            "a fearful spirit guarding the mighty sword!\n";
         }
         says += "The Oracle returns to her meditating and says no more.";
      } else {
         says += "\n" + say_start() + "You need three special rings before I can help you.";
      }
      remember(str);
      quester->simple_action(say_start() + says);
   }
}
