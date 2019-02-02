#include "../../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

static string *acts;
static int index;

void setup(void) {
   set_name("jerry");
   add_id("the regular");
   set_gender("male");
   set_short("Jerry the regular");
   set_long("Jerry can always be found hanging out " +
      "in the shop. He doesn't have much else to " +
      "do. It seems like he's never really listening.");
   set_race("human");
   index = 0;
   acts = ({
      "say Mhm.",
      "say Interesting.",
      "say Sure enough.",
      "say That's right.",
      "say You don't say.",
      "say Inconceivable.",
      "say How about that.",
      "say Who would have thunk.",
      "say I've heard that before.",
      "say I'm not so sure about that.",
      "emote nods."
   });
   set_level(NOKICLIFFS_MONSTER_LEVEL);
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE);
}

static int should_jerry_respond(string str) {
   string who;

   if (!empty_str(str) &&
         (sscanf(str, "%s says: %*s", who) > 0 ||
         sscanf(str, "%s says excitedly: %*s", who) > 0 ||
         sscanf(str, "%s asks: %*s", who) > 0)) {
      return who != "Jerry" && (who == "Bridgette" || random(2));
   }
   return 0;
}

void outside_message(string str) {
   if (is_fighting()) {
      return;
   }

   str = ANSI_D->strip_colors(str);
   if (should_jerry_respond(str)) {
      respond(acts[index++]);
      if (index == sizeof(acts)) {
         index = 0;
      }
   }
}
