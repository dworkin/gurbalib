#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("endurance potion");
   set_adj("endurance");
   add_ids("potion");
   set_short("A small potion of endurance");
   set_long("A small potion of endurance. Drinking it will make you " +
      "feel as if you could fight forever; or until you " +
      "run out of hit points, whichever comes first.\n");
   set_eatable(1);
   set_gettable(1);
   set_value(10);
   set_weight(2);
}

int do_eat(void) {
   write("You drink the potion. You feel your endurance boost.\n");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " drinks a potion of endurance.\n");
   this_player()->increase_end(this_player()->query_max_end());
   this_player()->set_performance_enhancement(25 + random(25));
   this_object()->destruct();
}
