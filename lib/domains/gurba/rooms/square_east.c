#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GurbaSquare");
   add_area("GurbaOutdoor");

   set_short("Gurba Town Square - East");
   set_long("Here on the eastern side of the town square, a large " +
      "crowd of merchants are trying to convince people to buy their " +
      "wares. The resulting bedlam is fantastically loud and utterly " +
      "disorganized. The bricks here are well-worn from the constant " +
      "traffic. Gelmir Road leads off towards the east from here.");

   set_exits(([
      "north" : DIR + "/rooms/square_northeast",
      "south" : DIR + "/rooms/square_southeast",
      "west" : DIR + "/rooms/square_center",
      "east" : DIR + "/rooms/gelmir1",
   ]));

   add_item("merchants", "These fine gentlemen and ladies work " +
      "tirelessly to promote the sales of their respective goods.");
}
