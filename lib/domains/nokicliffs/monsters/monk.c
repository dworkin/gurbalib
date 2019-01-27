#include "../domain.h"

inherit DIR + "/lib/monk";

void setup(void) {
   set_name("monk");
   set_short("A monk");
   set_long("The young monk stands here looking faithful. " +
      "He also looks like he knows how to handle himself in " +
      "the martial arts. Although clothed in nothing more than " +
      "a robe and some simple sandals you cannot shake the feeling " +
      "that this might be a new life for him.");
}

