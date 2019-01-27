#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("The dungeons");
   set_long("A long row of small dirty cells with heavy iron doors lies in front "
        + "of you. Though the castle has been uninhabited for many hundred years "
	  + "the dungeons seem to have been used recently... ");

   add_exit("north", CASTLE_ROOMS + "/corridor.c");

   add_item("dungeons", "There are dried pools of blood and vomit on the floor");
   add_item("floor", "The floor hasn't been washed in years");
   add_item("pools", "Ech....you stand away from the odor");
   add_item("rows", "Hundreds of prisoners must have been kept here at one time");
   add_item("cells", "They housed one prisoner each. Any more would have been barbaric");
   add_item("blood", "From the color, you believe it to be human blood. Strangely enough though, there seems to be some dark liquid dried up. Demon ichor, perhaps..");
   add_item("vomit", "Fortunately, in a way, you are not an expert on vomit. It looks normal");
   add_item("doors", "They look as if they have been rusted shut");

   set_objects(
         DIR + "/obj/cauldron/rat_skeleton.c",
         DIR + "/monsters/jailer.c"
   );

   add_action("open_cmd", "open");
   add_action("kick_cmd", "kick");
}

int open_cmd(string str) {
   if (str && (str == "door" || str == "doors")) {
      this_player()->simple_action("$N $vtry to open the doors but " +
         "they've been rusted shut.");
      return 1;
   }

   return 0;
}

int kick_cmd(string str) {
   if (str && (str == "door" || str == "doors")) {
      this_player()->simple_action("$N $vkick the door with all $p might and " +
         "$N $vhear something snap and $vhowl with pain.");
      return 1;
   }

   return 0;
}