#include "../domain.h"

inherit DIR + "/lib/vampire";

void setup(void) {
   set_name("trazom");
   set_short("Trazom the vampire");
   set_long("Trazom's cold dead flesh is desiccated, pulling his maw open " +
      "in a permament groaning position. His eyes are sunk deep in his " +
      "boney face. His hair is incredibly thin and wispy. He seems to " +
      "miss the days when he walked among the living as one of them.");
   set_race("vampire");
   set_aggressive(1);
}
