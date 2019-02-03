#include "../../domain.h"

inherit DIR + "/lib/safe";

static int alarms;

int can_open(object thief) {
   return ::can_open(thief) &&
      !thief->query_environment()->present("bank guard");
}

private int has_stethoscope(object thief) {
   object *inv;
   int     i, dim;

   inv = thief->query_inventory();
   dim = sizeof(inv);
   for (i = 0; i < dim; i++) {
      if (inv[i]->is_id("stethoscope")) {
         return 1;
      }
   }

   return 0;
}

private object find_guard(object thief) {
   return thief->query_environment()->present("bank guard");
}

void summon_guard(object thief, object stethoscope, int unlocked) {
   if (!alarms) {
      this_environment()->tell_room(nil, "The bank alarms start " +
         "blaring. It's difficult to concentrate. But you " +
         "should hurry, the guard has been summoned.");
      if (!unlocked) {
         thief->message("You can use your stethoscope to stay " +
            "focused on breaking into the vault before the " +
            "bank guard arrives.");
      }
      call_out("bring_in_guard", 8);
      alarms = 1;
   }
}

void bring_in_guard(void) {
   object guard;
   guard = clone_object(DIR + "/monsters/bank_guard.c");
   guard->setup();
   guard->move(this_environment());
   this_environment()->tell_room(nil,
      "The bank's guard shows up and is ready to do his job. " +
      "The bank's alarms switch off.");
   guard->respond("say Alright who's lookin' for a beat down?");
   alarms = 0;
}

void notify_bad_turn(object thief, object stethoscope) {
   object guard;
   guard = find_guard(thief);
   if (guard) {
      guard->respond("emote chuckles mockingly.");
   }
}

void notify_good_turn(object thief, object stethoscope) {
   object guard;

   guard = find_guard(thief);
   if (guard) {
      guard->respond("emote doesn't look worried.");
   } else {
      summon_guard(thief, stethoscope, 0);
   }
}

void notify_unlock(object thief, object stethoscope) {
   object guard;
   guard = find_guard(thief);
   if (guard) {
      guard->respond("say You'll never get in. Never.");
   } else {
      summon_guard(thief, stethoscope, 1);
   }
}

string query_cannot_open_message(object thief) {
   object guard;
   int    professional_thief;

   professional_thief = has_stethoscope(thief);
   guard = thief->query_environment()->present("bank guard");
   if (guard) {
      if (professional_thief) {
         guard->respond("emote growls menacingly.");
         guard->respond("say Halt, thief!");
      } else {
         guard->respond("emote scoffs.");
         guard->respond("say Amateur.");
      }
      return "The guard stops you.";
   }
   
   return "The dial has not been turned in the proper " +
      "sequence yet. When it has been, the vault will " +
      "unlock and it can be opened.";
}

void setup(void) {
   set_id("vault");
   set_short("The bank vault");
   set_long("This is the bank's vault. On the door is a " +
      "dial. You can turn dial left or turn dial right " +
      "and try to break in, but only professionals really " +
      "have a chance.");
   set_open_state(0);
   alarms = 0;
}

