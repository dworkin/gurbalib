#include "../../domain.h"

inherit DIR + "/lib/murder_hobo";

void setup(void) {
   set_race("gnome");
   set_name("bard");
   set_short("A bard");
   set_long("The bard is wearing brightly colored clothes " +
      "and is often the first to die.");
   set_level(1);
   set_max_hp(10);
   set_hp(10);
}
