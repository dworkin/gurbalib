#include "../../domain.h"

inherit NOKICLIFFS_VENDOR;

#define INTERVAL 10

static int     count;
static string *acts;

void setup(void) {
   set_name("bridgette");
   add_ids("shop keeper", "shopkeeper");
   set_gender("female");
   set_race("human");
   set_level(1);
   set_short("Bridgette the shopkeeper");
   set_long("She is a comely young lass.");
   add_item(CLASSBEER, 20);
   add_item(COM_MEAL, 10);
   add_item(FIREBREATHER, 20);
   add_item(MUG, 20);
   add_item(SPECIAL, 20);
   add_item(TORCH, 10);
   add_item(DIR + "/obj/climbing_gear", 1);
   count = 0;
   acts = ({ 
      "emote smiles politely.",
      "emote smiles.",
      "emote blinks.",
      "emote spaces out.",
      "emote raises one eyebrow.",
      "emote sighs contentedly.",
      "emote scratches her head.",
      "say You can 'list' what's for sale.",
      "say We restock as quickly as possible.",
      "say Stay as long as you like.",
      "say Welcome, traveler.",
      "say Thanks for visting.",
      "say Noki Town is a great to place to visit. " +
         "And to live.",
      "say Don't forget to check out the smithy. " +
         "It's at the northern edge of town.",
      "say The bank is quite secure.",
      "say Mmm, lunch.",
      "say I don't like Harry the Affectionate much.",
      "say I'm not much of a morning person.",
      "say I like watching puddles gather rain.",
      "say The closers never do their job."
   });
}

void do_extra_actions(void) {
   if (is_fighting()) {
      return;
   }

   /* XXX give approx time to restock. */

   if (count++ > INTERVAL) {
      if (random(2)) {
         respond(random_element(acts));
         count = 0;
      }
   }
}

int asks_or_says_about_restocking(string str) {
   string who, what;
   return (sscanf(str, "%s asks: %s", who, what) == 2 ||
         sscanf(str, "%s says: %s", who, what) == 2 ||
         sscanf(str, "%s says excitedly: %s", who, what) == 2) ?
         (strstr(what, "restock") > -1 && who != "Bridgette") : 0;
}

void outside_message(string str) {
   str = lowercase(ANSI_D->strip_colors(str));
   if (asks_or_says_about_restocking(str)) {
      if (is_fighting()) {
         respond("say Kinda busy here!");
         return;
      }
      /* XXX she can say how many minutes. */
   }
}
