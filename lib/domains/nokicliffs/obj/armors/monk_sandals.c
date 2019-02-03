#include "../../domain.h"

inherit DIR + "/lib/armor";

void setup(void) {
   set_id("sandals");
   set_short("A pair of monk's sandals");
   set_long("A pair of monk's boots. " +
      "These are made of very simple materials and skill. " +
      "They were probably made by the monk who was wearing " +
      "them upon the time of his demise. " +
      "However did you come by a pair of these?");

   set_slot("feet");
   set_ac(0);
   set_weight(1);
   set_value(1);
}
