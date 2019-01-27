#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("Torture chamber");
   set_long("This is the torture chamber of the castle. Around the walls "
            + "hang various tools for inflicting as much pain as possible to "
            + "the victims. Their screams still seem to linger in the air.");
   add_exit("north", CASTLE_ROOMS + "/downstairs.c");

   add_item("chamber", "The chamber has a thin coating of blood on the floor.");
   add_item("tools", "Standard torture tools. You shudder as you move near them.");
   add_item("screams", "They echo in your ear, though you know them to be false.");

   set_objects(DIR + "/obj/weapons/whip.c");

   add_action("listen_cmd", "listen");
}

int listen_cmd(string str) {
   if (empty_str(str)) {
      this_player()->simple_action("$N $vperk up $p ears; $N can almost hear "+
         "someone screaming in pain, though $n $vknow them to be false.");
      return 1;
   }

   if (str == "to screaming" || str == "to screams" || str == "someone screaming") {
      this_player()->simple_action("$N $vlisten to the sound of someone " +
         "screaming in pain, though $n $vknow them to be false.");
      return 1;
   }

   return 0;
}
