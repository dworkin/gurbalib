#include "../domain.h"

inherit "/std/object";
inherit NOKICLIFFS_HEALING_LIB;

void setup(void) {
   set_id("mana potion");
   add_ids("potion");
   set_short("A mana potion");
   set_long("The mana potion is in a " +
            "small rectangular glass bottle with a cork stopper. " +
            "The potion is a swirling thick blue colored " +
            "liquid, which is quite viscuous but drinkable. " +
            "Drink this potion to recover some of your spent mana.");
   set_eatable(1);
   set_gettable(1);
   set_value(100);
   set_weight(1);
}

int do_eat(void) {
   set_doctor(this_object());
   set_patient(this_player());
   recover_mana(max_mana, nil);
   recover_mana(10, "$N $vdrink a mana recovery potion.");
   this_object()->destruct();
   return 1;
}
