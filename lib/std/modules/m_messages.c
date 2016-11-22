#include <type.h>

#define ENDS_WITH_Y ({ "enjoy", "toy", "employ", "deploy" })

string *compose_message(object who, string msg, object target,
   varargs mixed * objs) {
   string *words, us, them, others, tmp;
   int punc, i, objnum, pronounFlag;

   us = "";
   them = "";
   others = "";

   if (msg && msg != "") {
      words = explode(msg, " ");
   } else {
      return (({ us, them, others }));
   }

   for (i = 0; i < sizeof(words); i++) {
      if (words[i] == "") {
         continue;
      }

      if (words[i][0] == '$' && strlen(words[i]) >= 2) {

         if (words[i][strlen(words[i]) - 1] == '.' ||
            words[i][strlen(words[i]) - 1] == ',' ||
            words[i][strlen(words[i]) - 1] == '!' ||
            words[i][strlen(words[i]) - 1] == '?') {

            punc = words[i][strlen(words[i]) - 1];
            words[i] = words[i][..strlen(words[i]) - 2];
         } else {
            punc = 0;
         }
         if (pronounFlag == 1 && words[i][1] != 'o') {
            pronounFlag = 0;
         }
         switch (words[i][1]) {
            case 'N':
               if (who->is_living()) {
                  if (!who->query_name()) {
                     us += "you ";
                     them += "the " + who->query_id() + " ";
                     others += "the " + who->query_id() + " ";
                  } else {
                     us += "you ";
                     them += who->query_Name() + " ";
                     others += who->query_Name() + " ";
                  }
               } else {
                  us += "you ";
                  them += "the " + who->query_id() + " ";
                  others += "the " + who->query_id() + " ";
               }

               break;
            case 'n':
               us += "you ";
               them += who->query_gender_pronoun() + " ";
               others += who->query_gender_pronoun() + " ";
               break;
            case 'p':
               us += "your ";
               them += who->query_gender_possessive() + " ";
               others += who->query_gender_possessive() + " ";
               pronounFlag = 1;
               break;
            case 'P': /* capital P */
               us += "your ";
               them += who->query_gender_determiner()  + " ";
               others += who->query_gender_determiner()  + " ";
               pronounFlag = 1;
               break;
            case 'v':
               if (strlen(words[i]) < 3) {
                  break;
               }

               us += words[i][2..] + " ";

               if (words[i][2..] == "are") {
                  them += "is ";
                  others += "is ";
               } else if (words[i][2..] == "say:") {
                  them += "says: ";
                  others += "says: ";
               } else if (words[i][2..] == "ask:") {
                  them += "asks: ";
                  others += "asks: ";
               } else if (words[i][2..] == "remark:") {
                  them += "remarks: ";
                  others += "remarks: ";
               } else if (words[i][2..] == "mumble:") {
                  them += "mumble: ";
                  others += "mumbles: ";
               } else if (words[i][2..] == "shout:") {
                  them += "shouts: ";
                  others += "shouts: ";
               } else if (words[i][2..] == "ponder:") {
                  them += "ponders: ";
                  others += "ponders: ";
               } else if (words[i][2..] == "whisper:") {
                  them += "whispers: ";
                  others += "whispers: ";
               } else if (words[i][2..] == "exclaim:") {
                  them += "exclaims: ";
                  others += "exclaims: ";
               } else if (words[i][2..] == "mutter:") {
                  them += "mutters: ";
                  others += "mutters: ";
               } else if (words[i][2..] == "say") {
                  them += "says ";
                  others += "says ";
               } else if (words[i][strlen(words[i]) - 1] == 'o') {
                  them += words[i][2..] + "es ";
                  others += words[i][2..] + "es ";
               } else if (words[i][strlen(words[i]) - 1] == 'h' &&
                  words[i][strlen(words[i]) - 2] != 'g') {
                  them += words[i][2..] + "es ";
                  others += words[i][2..] + "es ";
               } else if (words[i][strlen(words[i]) - 1] == 'y') {
                  if (member_array(words[i][2..], ENDS_WITH_Y) == -1) {
                     them += words[i][2..strlen(words[i]) - 2] + "ies ";
                     others += words[i][2..strlen(words[i]) - 2] + "ies ";
                  } else {
                     them += words[i][2..] + "s ";
                     others += words[i][2..] + "s ";
                  }
               } else if (words[i][strlen(words[i]) - 1] == 's') {
                  them += words[i][2..] + "es ";
                  others += words[i][2..] + "es ";
               } else {
                  them += words[i][2..] + "s ";
                  others += words[i][2..] + "s ";
               }
               break;
            case 'T':
               if (who == target) {
                  /* Doing something to ourselves. */
                  us += "yourself ";
                  them += who->query_gender_reflexive() + " ";
                  others += who->query_gender_reflexive() + " ";
               } else {
                  if (target->is_living()) {
                     if (!target->query_Name()) {
                        us += "the " + target->query_id() + " ";
                        them += "you ";
                        others += "the " + target->query_id() + " ";
                     } else {
                        us += target->query_Name() + " ";
                        them += "you ";
                        others += target->query_Name() + " ";
                     }
                  } else {
                     us += "the " + target->query_id() + " ";
                     them += "you " + target->query_id() + " ";
                     others += "the " + target->query_id() + " ";
                  }
               }
               break;
            case 't':
               if (who == target) {
                  /* Doing something to ourselves. */
                  us += "yourself ";
                  them += who->query_gender_reflexive() + " ";
                  others += who->query_gender_reflexive() + " ";
               } else {
                  if (target->is_living()) {
                     if (!target->query_Name()) {
                        us += "the " + target->query_id() + " ";
                        them += "you ";
                        others += "the " + target->query_id() + " ";
                     } else {
                        us += target->query_Name() + " ";
                        them += "you ";
                        others += target->query_Name() + " ";
                     }
                  } else {
                     us += "the " + target->query_id() + " ";
                     them += "you " + target->query_id() + " ";
                     others += "the " + target->query_id() + " ";
                  }
               }
               break;
            case 'o':
               if (strlen(words[i]) > 2 && words[i][2] >= '0'
                  && words[i][2] <= '9') {
                  objnum = words[i][2] - '0';
               } else {
                  objnum = 0;
               }
               if (!objs || !objs[objnum]) {
                  break;
               }
               if (typeof(objs[objnum]) == T_STRING) {
                  us += objs[objnum] + " ";
                  them += objs[objnum] + " ";
                  others += objs[objnum] + " ";
               } else {
                  if (!pronounFlag) { 
                     us += "the ";
                     them += "the ";
                     others += "the ";
                  }

                  us += objs[objnum]->query_id() + " ";
                  them += objs[objnum]->query_id() + " ";
                  others += objs[objnum]->query_id() + " ";
                  pronounFlag = 0;
               }
               break;
         }

         if (punc) {
            us[strlen(us) - 1] = punc;
            them[strlen(them) - 1] = punc;
            others[strlen(others) - 1] = punc;
            us += " ";
            them += " ";
            others += " ";
         }
      } else {
         us += words[i] + " ";
         them += words[i] + " ";
         others += words[i] + " ";
      }
   }
   if (us[strlen(us) - 1] == ' ') {
      /* We need to strip the final space. */
      us = us[..strlen(us) - 2];
      them = them[..strlen(them) - 2];
      others = others[..strlen(others) - 2];
   }

   return (( { us, them, others } ));
}

void targeted_action(string msg, object target, varargs mixed objs ...) {
   string *result;
   object room;

   catch {
      result = compose_message(this_object(), msg, target, objs);
      room = this_object()->query_environment();
      if (room) {
         room->tell_room(this_object(), result[2], target);
      }

      this_object()->message(capitalize(result[0]));

      if (target && target->is_living() && target != this_object()) {
         target->message(capitalize(result[1]));
         target->outside_message(capitalize(result[1]));
      }
   }:{
      console_msg("targeted_action ERROR: " + caught_error(1) + "\n");
      rethrow();
   }
}

void simple_action(string msg, varargs mixed objs ...) {
   targeted_action(msg, nil, objs);
}

void other_action(object who, string msg, object target, 
   varargs mixed objs ...) {
   string *result;
   object room;

   result = compose_message(who, msg, target, objs);
   room = this_object()->query_environment();
   if (!room) { 
      return;
   }
   room->tell_room(who, result[2], target);
   if (target && target->is_living() && target != who) {
      target->message(capitalize(result[1]));
   }
}
