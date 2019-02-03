#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("smith");
   add_id("angmar's smith");
   set_gender("male");
   set_race("human");
   set_short("Angmar's smith");
   set_long("The smith sighs. He is locked into the service of Angmar unto death. " +
      "The smith will value armors and weapons " +
      "for a reasonable fee." +
      "\n\t'cost item' shows what the smith would take to value the item." +
      "\n\t'show item' shows the item to the smith.");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", BASE_OFFENSE);
   set_skill("combat/defense", BASE_DEFENSE);
}
