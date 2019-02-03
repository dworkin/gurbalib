#include "../../domain.h"

inherit DIR + "/lib/sword";

void setup(void) {
   ::setup();
   set_id("lawbringer");
   set_short("The Lawbringer of Balance");
   set_long("This is the legendary Lawbringer of Balance. " +
      "Many believe that this sword was forged in ancient times " +
      "by a dwarven king with a hammer borrowed from a god, using " +
      "a dragon's breath to heat the steel. Then nine Great Wizards " +
      "of Law enchanted the blade with a powerful spell, and was " +
      "thus created one of the most formidable weapons ever to be seen.");
}
