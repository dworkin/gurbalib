#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("rejuvination potion");
   add_ids("potion");
   set_short("A rejuvination potion");
   set_long("Drink this when you need full body healing.");
   set_eatable(1);
   set_gettable(1);
   set_value(2);
   set_weight(1);
}

int do_eat(void) {
   string str, race;
   int    max_hp, max_mana, max_end;

   max_hp = this_player()->query_max_hp();
   max_mana = this_player()->query_max_mana();
   max_end = this_player()->query_max_end();
   race = this_player()->query_race();
   this_player()->increase_hp(max_hp);
   this_player()->increase_mana(max_mana);
   this_player()->increase_end(max_end);

   str = "$N $vdrink a potion of rejuvination " +
      "and $vlook like a new " + race + ". " +
      "The potion itself disappears in a puff of " +
      "smoke.";
   this_player()->targeted_action(str, this_player());
   this_object()->destruct();
}
