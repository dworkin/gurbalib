#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_short("In a cornfield");
   set_long("You are in a large cornfield. It's full of corn.");

   add_exit("south", FAIRYLAND_ROOMS + "/corn1.c");

   add_item("cornfield", "The field stretches on for acres");
   add_item("corn", "It must be a bumper crop this year. There are ears everywhere");
   add_item("ears", "Ears of corn. But they are not ripe yet, so don't try to pick them");
   add_item("crop", "This huge expanse of corn should make the farmer very happy");

   set_objects(DIR + "/monsters/scarecrow.c", DIR + "/obj/cauldron/corn_cob.c");

   add_action("pick_cmd", "pick");
   add_action("take_cmd", "get");
   add_action("take_cmd", "steal");
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

int take_cmd(string str) {
   object scarecrow, corn_cob;

   if (empty_str(str)) {
      return 0;
   }

   scarecrow = this_object()->present("scarecrow");
   corn_cob = this_object()->present("corn cob");

   if (!scarecrow) {
      return 0;
   }

   if (corn_cob && (corn_cob->is_id(str) || str == "all")) {
      if (scarecrow->is_fighting()) {
         this_player()->simple_action("$N $vtry to take the corn cob, " +
            "but the scarecrow is already defending it.");
         return 1;
      }

      this_player()->simple_action("$N $vtry to take the corn cob, " +
         "which the scarecrow notices and $vgrab $p hand!");
      scarecrow->respond("attack " + this_player()->query_name());
      return 1;
   }

   return 0;
}
