#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("Gurba");
   add_area("GurbaSquare");
   add_area("GurbaOutdoor");

   set_short("Gurba Town Square - North");
   set_long("The northern side of the town square is full of street " +
      "performers and musicians, all of whom are trying to outdo the " +
      "others. The townsfolk watch them, cheering, booing, and " +
      "occasionally giving them some money. The area is a whirling, " +
      "loud amalgam of sound and color, full of dancing and mildly " +
      "clashing notes from a wide array of musical instruments. " +
      "Borland Avenue heads northward from this point.");

   set_exits(([
      "east" : DIR + "/rooms/square_northeast",
      "west" : DIR + "/rooms/square_northwest",
      "south" : DIR + "/rooms/square_center",
      "north" : DIR + "/rooms/borland1",
   ]));

   add_item("performers", "Men and women dance around you wearing " +
      "brightly colored clothes, while others are busy performing an " +
      "improbable set of clever illusions and acrobatic stunts.");
   add_item("musicians", "Countless artists of the musical persuasion " +
      "are scattered around the area, playing their instruments with " +
      "varying degrees of skill and almost no regard for anything else.");
}
