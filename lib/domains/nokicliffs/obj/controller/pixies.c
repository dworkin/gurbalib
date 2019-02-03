#include "../../domain.h"

mapping cursed;

static void restore_me(void) {
   unguarded("restore_object", PIXIES_DATA);
}

static void save_me(void) {
   unguarded("save_object", PIXIES_DATA);
}

private void end_curse(string victim) {
   cursed[victim] = nil;
}

private void decay_curse(string victim) {
   if (member_map(victim, cursed)) {
      call_out("suffer_curse", cursed[victim][1], victim);
      cursed[victim][0] -= cursed[victim][1];
   }
}

private void after_suffer_curse(string victim) {
   if (cursed[victim][0] > 0) {
      decay_curse(victim);
   } else {
      end_curse(victim);
   }
}

void suffer_curse(string victim) {
   object env, vic;
   string str;
   vic = USER_D->find_player(victim);
   if (vic && !nilp(cursed) && cursed[victim][0] > 0) {
      switch (random(7)) {
         case 0:
            str = "$N $vgiggle like a school kid.";
            break;
         case 1:
            str = "$N $vtitter like a wagonload of maidens.";
            break;
         case 2:
            str = "$N $vchortle with glee.";
            break;
         case 3:
            str = "$N $vfeel like dancing!";
            break;
         case 4:
            str = "$N $vgrin from ear to ear.";
            break;
         case 5:
            str = "$N $vsmirk like the cat who ate the canary.";
            break;
         default:
            str = "$N $vfeel like a nut.";
      }
      vic->targeted_action(str, vic);
   }
   after_suffer_curse(victim);
   save_me();
}

void create(void) {
   if (nilp(cursed)) {
      cursed = ([ ]);
   }
   if (file_exists(PIXIES_DATA)) {
      restore_me();
      return;
   }
   save_me();
}

void curse(string victim, int duration, int interval) {
   cursed[victim] = ({ duration, interval });
   save_me();
   call_out("suffer_curse", cursed[victim][1], victim);
}

