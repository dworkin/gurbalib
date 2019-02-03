#include "../../domain.h"

inherit "/std/object";
inherit "/std/modules/m_readable";

void setup(void) {
  set_id("recipe");
  add_id("angmars recipe");
  set_short("A recipe");
  set_long("There is a recipe written on it that you can read.");
  set_value(10);
  set_weight(1);
  set_gettable(1);
  set_message("Ingredients:\n\n" +
     (CORPSE_GETTABLE ? "The fresh corpse of a monster\n" : "") +
     "A dead fish\n" +
     "A slimy mushroom\n" +
     "A corncob\n" +
     "The skeleton of a rat\n\n" +
     "Mix all ingredients in a magically prepared container.\n" +
     "Add this recipe to the mixture and speak the magic words:\n" +
     "'kashmirak gorondolum'\n");
}
