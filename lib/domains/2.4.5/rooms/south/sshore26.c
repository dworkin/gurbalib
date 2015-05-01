#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("The shore of Crescent Lake");
   set_long("You are standing on the shore of Crescent Lake, a beautiful " +
      "and clear lake.  Out in the center of the lake stands the Isle " +
      "of the Magi.  A Trail lead into the forest to the north." +
      "The shore of Crescent Lake continues northeast and northwest.  " +
      "To the southeast, a stone bridge used to cross over to the " +
      "Isle of the Magi, but it has fallen into the lake, making the " +
      "crossing to the island impossible by that means.");

   add_exit("north", DIR + "/rooms/south/sforst46.c");
   add_exit("northeast", DIR + "/rooms/south/sshore27.c");
   add_exit("northwest", DIR + "/rooms/south/sshore25.c");
   add_exit("southeast", "#go_southeast");
}

string query_long() {
   string str;

   str = "You are standing on the shore of Crescent Lake, a beautiful " +
      "and clear lake.  Out in the center of the lake stands the Isle " +
      "of the Magi.  A Trail lead into the forest to the north." +
      "The shore of Crescent Lake continues northeast and northwest.  " +
      "To the southeast, a stone bridge used to cross over to the " +
      "Isle of the Magi, but it has fallen into the lake, making the " +
      "crossing to the island impossible by that means.";

   if (this_player()->query_level() > 15) {
      str += "  However, you can make out the faint outline of a magical " +
         "bridge in its place.";
   }
   return str;
}

int go_southeast() {
   string usermsg, othermsg;

   if (this_player()->query_level() <= 15) {
      write("The bridge to the Isle of the Magi has collapsed, making the " +
         "trip across impossible.");
      return 1;
   }
   add_exit("southeast", DIR + "/rooms/south/sislnd1.c");
   usermsg = "Trusting in your faith, you step onto the magical bridge " +
      "and move across to the Isle of the Magi.";
   othermsg =  this_player()->query_Name() + " walks across a faintly " +
      "glowing bridge.";

   /* XXX domove(DIR + "/rooms/south/sislnd1.c", usermsg, othermsg); */
   return 1;
}
