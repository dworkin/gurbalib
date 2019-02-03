#include "../../domain.h"

inherit DIR + "/lib/murder_hobo";

#define INTERVAL 2
static int count;

private int should_shoot(void) {
   return is_fighting() &&
      this_object()->query_environment()->present("beast");
}

void do_extra_actions(void) {
   if (++count >= INTERVAL) {
      if (should_shoot()) {
         if (query_mana() < 5 && !random(3)) {
            respond("frown");
            return;
         }
         respond("cast missile beast");
         this_object()->query_environment()->tell_room(nil,
            "A soft glow shoots out of mage's hand and hits the beast.");
      }
      count = 0;
   }

   ::do_extra_actions();
}

void setup(void) {
   set_race("elf");
   set_name("mage");
   set_short("A mage");
   set_long("The mage is the party's spell caster. " +
      "Better keep an eye out.");

   set_max_mana(query_max_mana() * (random(3) + 1));
   set_mana(query_max_mana());

   equip_murder_hobo(({
      NOKICLIFFS_ARMORS_DIR + "/simple_cloak.c",
      NOKICLIFFS_WEAPONS_DIR + "/dagger.c"
   }));
}
