#include "../../domain.h"

inherit DIR + "/lib/room";

int do_drop_sea_shell(string str) {
   object shell, beads;
   string s;

   if (sscanf(str, "%s in fountain", s) == 1) {
      if (s == "sea shell" || s == "shell" || s == "pretty sea shell") {
         shell = this_player()->present("sea shell");
         if (!shell) {
            write("You don't have one anyway.");
            return 1;
         }

         shell->destruct();
         this_player()->targeted_action("$N $vtoss a pretty sea shell " +
            "into the village fountain. *plunk*", this_player());

         if (!this_player()->present("beads")) {
            beads = clone_object(NOKICLIFFS_DIMENSIONAL_BEADS);
            beads->setup();
            beads->set_owner_name(this_player());
            beads->move(this_player());
            write("You have been rewarded with a string of dimensional " +
               "beads.");
         }

         return 1;
      }
   }

   this_player()->targeted_action("$N $vthink twice about littering.",
         this_player());

   return 1;
}

void setup(void) {
   set_short("Noki Town central square");
   set_long("You are in the middle of the Noki Town " +
      "square. A large fountain of crisp, clear mountain " +
      "melt water is here. Quite curiously, there are some " +
      "pretty sea shells in the " +
      "fountain that people have tossed in upon making " +
      "wishes. It would not be nice of you to take them. " +
      "Elsewhere, villagers are milling about, taking care of their " +
      "business. You can go north to the northern end " +
      "of the town square, south to the southern end " +
      "of it; or you can go east to the chapel or " +
      "west to the shop.");

   add_item("fountain", "The fountain bubbles with fresh " +
      "mountain melt water. A few pretty sea shells are in the " +
      "fountain from the villagers.");
   add_item("villagers", "The villagers are milling about, " +
      "taking care of their business.");

   set_exits(([
      "north" : DIR + "/rooms/town/square_north.c",
      "south" : DIR + "/rooms/town/square_south.c",
      "east" : DIR + "/rooms/town/chapel.c",
      "west" : DIR + "/rooms/town/shop.c"
   ]));

   add_action("do_drop_sea_shell", "toss");
   add_action("do_drop_sea_shell", "throw");
}

