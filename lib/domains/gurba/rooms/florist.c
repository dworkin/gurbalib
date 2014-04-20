#include "../domain.h"

inherit "/std/room";

void setup(void) {
   set_short("Frida's Florist");
   set_long("This small room is the flower shop. Colorful bouquets poke " +
      "out from everywhere in the room. Flowerpots of all colors house " +
      "the dozens of different flowers at sale here. ");
   set_exits(([
      "northeast" : DIR + "/rooms/square_southwest",
   ]));

   add_item("flowers", "She has a lot of them, in all the colors of the " +
      "rainbow. When you study them you also smell the delightful " +
      "variety of scents they have.");
   add_item("flowerpots", "pots", "pot", "flowerpot", "All different " +
      "sizes, shapes, and colors. Mostly made out of clay or wood.");

   set_objects(
      DIR + "/monsters/frida",
      "/domains/required/objects/mer_sign"
   );
}
