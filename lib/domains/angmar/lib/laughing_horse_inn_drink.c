#include "../domain.h"

inherit "/std/object";

nomask int is_laughing_horse_in_drink(void) {
   return TRUE;
}

void create(void) {
   ::create();
   set_eatable(1);
   set_gettable(1);
   set_weight(1);
}

int can_move(object obj) {
   return obj && obj->is_player();
}

int do_eat(void) {
   this_player()->simple_action("$N $venjoy $p drink.");
   this_player()->increase_hp(12 + random(2));
   this_object()->destruct();

   return 1;
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The drink breaks into pieces as it hits the ground.");
   this_object()->destruct();
}
