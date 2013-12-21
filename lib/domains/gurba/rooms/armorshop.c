#include "../domain.h"

inherit "/std/room";

void setup(void) {
   set_short("Timoth's Armorarium");
   set_long("This small but well-maintained shop smells strongly of " +
      "armor polish. This is no surprise, since the walls are covered in " +
      "all manner of gleaming plate armor and leather clothing. As the " +
      "primary supplier of armor for the fighters of Gurba's Fighter's " +
      "Guild, Timoth (a centaur) does quite a respectable business. " +
      "Indeed, hardly a minute goes by where a fighter doesn't show up " +
      "asking for a new breastplate or a repair of some kind.");

   set_exits(([
      "north" : DIR + "/rooms/square_southeast",
   ]));

   add_item("armor", "armors", "shields", "shield",
      "Shields and armor for all races.");
   add_item("plaque", "The plaque says: \"Timoth's Armorarium: We'd " +
      "rather be safe than sorry!\"");
}
