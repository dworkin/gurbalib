#include "../domain.h"

inherit "/std/object";
inherit "/std/modules/m_openable";
inherit "/std/modules/m_readable";

static int recipe_flag;

void setup(void) {
   set_id("notebook");
   set_short("A notebook");
   set_long("\"It is a small notebook with various formulas scribbled in it.");
   set_gettable(1);
   set_value(10);
   set_weight(1);
   set_open_state(0);
}

int do_open(object who) {
   int x;
   object recipe;

   x = ::do_open(who);

   if (x == 1 && recipe_flag == 0) {
      who->simple_action("As $N $vopen the notebook, something falls out of it to the ground.");
      recipe = clone_object(DIR + "/obj/cauldron/recipe.c");
      recipe->setup();
      recipe->move(who->query_environment());
      recipe_flag = 1;
   }

   return x;
}

int do_read(object who) {
   if (is_closed()) {
      this_player()->simple_action("$N $vtry to read a closed notebook.");
   } else {
      this_player()->simple_action("$N $vread the notebook but cannot understand the language.");
   }
   return 1;
}
