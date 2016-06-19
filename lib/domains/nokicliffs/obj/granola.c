#include "../domain.h"

inherit "/std/object";
inherit NOKICLIFFS_HEALING_LIB;

void setup(void) {
   set_id("granola");
   set_short("Some granola for the mind and body");
   set_long("The granola is not only tasty but also good for " +
      "the mind and the body.");
   set_eatable(1);
   set_gettable(1);
   set_value(2);
   set_weight(1);
}

int do_eat(void) {
   int    max_hp, max_mana;

   set_doctor(this_player());
   set_patient(this_player());
   recover_hp(5 + random(5), nil);
   recover_mana(5 + random(5),
      "$N $veat some granola and $vfeel better in mind and body.");
   this_object()->destruct();
   return 1;
}
