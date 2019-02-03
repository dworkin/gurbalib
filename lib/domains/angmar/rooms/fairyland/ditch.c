#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(FAIRYLAND_AREA);

   set_light(0);

   set_short("A ditch");
   set_long("You are in a ditch. Get up, you are making yourself dirty!");

   add_exit("east", FAIRYLAND_ROOMS + "/meadow.c");
   add_exit("west", FAIRYLAND_ROOMS + "/corn1.c");

   add_item("ditch", "It's filled with mud, dirt, and water.");
   add_item("mud", "There's nothing to be found in the mud.");
   add_item("dirt", "It does nothing but get your armour dirty.");
   add_item("water", "It does nothing but ruin your weapons.");

   add_action("drink_water_cmd", "drink");
}

int drink_water_cmd(string str) {
   if (str && (str == "water" || str == "ditch water")) {
      this_player()->simple_action("$N $vcup $p hands for some water from the ditch, " +
         "but $vthink better of it upon noticing all the blood in the water.");
      return 1;
   }

   return 0;
}

int do_search(void) {
   object candy;

   candy = this_object()->present("candy");
   if (!candy) {
      candy = clone_object(DIR + "/obj/candy.c");
      candy->setup();
      candy->move(this_object());
      this_player()->simple_action("$N $vfind a piece of candy in the ditch.");
      return 1;
   }

   return 0;
}
