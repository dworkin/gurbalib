#include "../../domain.h"

inherit "/domains/required/lib/sword";

int wield_hook(object player) {
   if (player->is_player()) {
      player->message("The sword twists away from your grip, hovers " + 
         "in the air and looks at you. Then it laughs contemptuously " +
         "and disappears in a blinding flash.\n" +
         "You think you hear the words 'puny mortal!' from " +
         "somewhere far away...");
      player->message("Should move it from your inventory.");
      return 0;
   }

   return 1;
}

void setup() {
   ::setup();
   set_id("chaosblade");
   set_short("A chaosblade of death");
   set_long("This is a slim but very heavy sword that seems " +
      "to glow with soft darkness. It looks strangely unnatural, " +
      "and it would probably be a bad move even to try to wield " + 
      "this weapon. Maybe someone else wants it? Come to think " +
      "of it, perhaps ther eis somewhere you could bring this " +
      "sword and collect a reward?");
   set_combat_stats(1, 10, 10);
   set_sword_skill("large");
   set_weight(3);
}
