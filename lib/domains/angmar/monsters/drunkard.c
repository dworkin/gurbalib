#include "../domain.h"

inherit "/std/monster";

string *messages;
string *attack_messages;

void do_extra_actions(void) {
   if (is_fighting()) {
      if (random(100) < 40) {
         respond(random_element(attack_messages));
         return;
      }
   }

   if (random(100) < 15) {
      respond(random_element(messages));
   }
}

void setup(void) {
   set_name("drunkard");
   set_short("A drunkard");
   set_long("The drunkard enjoys drinking at the Laughing Horse Inn.");

   set_race("human");
   set_level(15);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE * 5);

   attack_messages = allocate(3);
   messages = allocate(3);
   attack_messages[0] = "say Schtop that!";
   attack_messages[1] = "say What do you think you're doing?";
   attack_messages[2] = "emote holds the beer in one hand while he tries to hit you with his other hand.";
   messages[0] = "say I've schlayed many dragonsch in my life!";
   messages[1] = "say I'm a great dragonschlayer!";
   messages[2] = "say I know of a big dragon in the mountainsch nearby. " +
         "I'm gonna kill him today, but I muscht have another beer first.";

   set_objects(
         DIR + "/obj/amulet.c",
         DIR + "/obj/doors/mountain_key.c"
   );
}
