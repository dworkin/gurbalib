#include "../../domain.h"

inherit "/std/room";

void setup(void) {
  add_area(AREA);
  add_area(CASTLE_AREA);
  set_short("Angmar's castle");
  set_long("You are inside the gates of Angmar the Necromancer's castle. " +
           "The castle was abandoned a long time ago when Angmar was driven " +
           "from this world by the Istari, and is now quite ruined. Angmar's " +
           "workroom is to the east. You can see a forge to the west. ");

  add_exit("north", "/domains/2.4.5/rooms/vill_shore.c");
  add_exit("south", CASTLE_ROOMS + "/stairs.c");
  add_exit("west", CASTLE_ROOMS + "/forge.c");

  add_item("gates", "The gates are covered with rust, since they have not been used in ages.");
  add_item("rust", "The rust on the gates is thinck. The metal has oxidized over the years.");
  add_item("castle", "The castle looms over you. You shiver as you think of the death inside.");
  add_item("workroom", "The portal is shadowy. You see a few blurs inside.");
  add_item("portal", "The portal consists of a dark oval. You cannot see within.");
  add_item("oval", "The oval is a two-dimensional object. You are always facing it.");
  add_item("blurs", "You cannot distinguish anything about the blurs.");
  add_item("forge", "There's not much you can see from here.");
  add_item("sign", "The sign points south, and says, 'This way to Fairyland'.");
  add_item("south", "The way south is in darkness. You cannot see.");

  set_objects(
     DIR + "/monsters/creature.c"
  );
}
