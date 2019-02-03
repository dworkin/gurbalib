#include "../../domain.h"

inherit DIR + "/lib/sword";

int wield_hook(object player) {
   if (player->is_player()) {
      player->message("The sword twists away from your grip, hovers " + 
         "in the air and looks at you. Then it laughs contemptuously " +
         "and disappears in a blinding flash.\n" +
         "You think you hear the words 'puny mortal!' from " +
         "somewhere far away...");
      move(NOKICLIFFS_VOID);
      return 0;
   }

   return 1;
}

void setup(void) {
   ::setup();
   set_id("chaosblade");
   set_short("A chaosblade of death");
   set_long("This is a slim but very heavy sword that seems " +
      "to glow with soft darkness. It looks strangely unnatural, " +
      "and it would probably be a bad move even to try to wield " + 
      "this weapon. Maybe someone else wants it? Come to think " +
      "of it, perhaps there is somewhere you could bring this " +
      "sword and collect a reward?");
   set_sword_skill("large");
}
