#include "../../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

static string *acts;
static int     index;

void setup() {
   set_name("jerry");
   add_id("the regular");
   set_gender("male");
   set_short("Jerry the regular");
   set_long("Jerry can always be found hanging out " +
      "in the shop. He doesn't have much else to " +
      "do. It seems like he's never really listening.");
   set_race("human");
   set_level(1);
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
}

void outside_message(string str) {
   string who;

   if (is_fighting()) {
      return;
   }

   str = ANSI_D->strip_colors(str);
   if (sscanf(str, "%s says: %*s", who) > 0) {
      if (who != "Jerry" && (who == "Bridgette" || random(2))) {
         respond(acts[index++]);
         if (index == sizeof(acts)) {
            index = 0;
         }
      }
   }
}
