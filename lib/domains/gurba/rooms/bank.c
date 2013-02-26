#include "../domain.h"
inherit ROOM;

void setup(void) {
   set_short("Gurba Bank");
   set_long("This is the main bank branch of Gurba. There are two large " +
      "counters with a clerk behind each.  The floor and " +
      "columns supporting the roof are made of what appears to be marble.");

   set_exits(([
      "south" : DIR + "/rooms/border_south9",
   ]));

   add_item("counter", "counters",
      "Each of the counters are made out of solid oak.");
   add_item("clerk",
      "The clerks do not have any personalitly to speak of.  " +
      "You wonder if they are infact cardboard cutouts.");
   add_item("floor", "columns", "column", "The are nicely cut and tiled " +
      "out of what seems to be marble, though upon closer inspection it " +
      "seems to be fake.");

   set_objects(([
      "/domains/required/objects/bank_sign.c": 1,
   ]));
}
