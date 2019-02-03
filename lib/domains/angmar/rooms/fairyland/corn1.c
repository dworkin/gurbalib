#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_short("In a cornfield");
   set_long("You are in a large cornfield. Corn grows everywhere.");

   add_exit("north", FAIRYLAND_ROOMS + "/corn2.c");
   add_exit("east", FAIRYLAND_ROOMS + "/ditch.c");

   add_item("cornfield", "The field stretches on for acres");
   add_item("corn", "It must be a bumper crop this year. There are ears everywhere");
   add_item("ears", "Ears of corn. But they are not ripe yet, so don't try to pick them");
   add_item("crop", "This huge expanse of corn should make the farmer very happy");

   add_action("pick_cmd", "pick");
}

int pick_cmd(string str) {
   if (empty_str(str)) {
       return 0;
   }

   if (str == "corn" || str == "ears" || str == "ear" || str == "ear of corn" || str == "ears of corn") {
       this_player()->simple_action("$N $vthink about picking corn but $vrealize none are ripe yet.");
       return 1;
   }

   return 0;
}
