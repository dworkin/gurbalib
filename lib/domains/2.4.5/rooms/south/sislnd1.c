#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Link to the mainland");
   set_long("You are standing on the shore of the isle of the Magi.  " +
      "The shore of the island continues east and southwest from here " +
      "To the south, a hill rises up to the ancient ruins of the Tower " +
      "of Arcanarton, the archmage who used to live on this island.  " +
      "A magical bridge now stands on the ruins of the old stone bridge to " +
      "the northwest.");

   add_exit("south", DIR + "/rooms/south/sislnd13.c");
   add_exit("east", DIR + "/rooms/south/sislnd2.c");
   add_exit("northwest", "#go_northwest");
   add_exit("northeast", DIR + "/rooms/south/sislnd12.c");
}

void go_northwest(void) {
   string usermsg, othermsg;

   usermsg = "You trust in your faith and step out onto the near invisible " +
      "bridge."; 
   othermsg = this_player()->query_Name() + " walks across a faintly " +
      "glowing bridge.";
   /* XXX domove(DIR + "/rooms/south/sshore26.c",usermsg, othermsg); */
}
