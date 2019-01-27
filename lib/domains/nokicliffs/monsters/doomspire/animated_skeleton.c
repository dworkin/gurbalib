#include "../../domain.h"

inherit DIR + "/lib/monster";
inherit DIR + "/lib/simple_block";

#define INTERVAL 15
static int count;
static string *acts;

void do_extra_actions(void) {
   if (++count >= INTERVAL) {
      if (is_fighting()) {
         respond("emote punches its jaw back into its place.");
      } else {
         respond(random_element(acts));
         count = 0;
      }
   }
}

void setup(void) {
   set_name("skeleton");
   set_adj("animated");
   set_short("An animated skeleton");
   set_long("It takes some powerful necromantic magic to animated a " +
      "full skeleton like this.");
   set_hit_string("punch");
   add_block("up");

   acts = ({
      "say Tibia honest, I don't think you're gonna make it.",
      "say Well, I have a bone to pick with you.",
      "say Do you find this humerus?",
      "emote rattles its bones."
   });
}
