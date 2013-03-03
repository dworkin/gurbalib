#include "../../domain.h"
inherit ROOM;

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
/* XXX Need to add You trust in your faith and step out .... */
   add_exit("northwest", DIR + "/rooms/south/sshore26.c");
   add_exit("northeast", DIR + "/rooms/south/sislnd12.c");
}
