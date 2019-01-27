#include "../../domain.h"

inherit DIR + "/lib/armor";

string query_short(void) {
   string str;

   str = ::query_short();
   str += " [AC: " + query_ac() + "]";
   return str;
}

void setup(void) {
   set_id("hauberk");
   set_adj("magical");
   set_short("A magical hauberk of the immortals");
   set_long("A magical hauberk worn by the immortals. " +
      "The hauberk is crafted of metals imbued with extremely " +
      "powerful magicks guarding the wearer from all manner of " +
      "attack and damage. The metal shines with pure silver but " +
      "coursing across its surface are the aforementioned magicks, " +
      "causing slight, ever so slight, changes in the hauberk's hues. " +
      "The meanings of which are known only to the immortals and the " +
      "ancient smiths who forged this armor in the outer planes.");
   set_medium();
   set_ac(100);

   add_action("set_ac_cmd", "ac");
}

int set_ac_cmd(string arg) {
   int i;

   if (empty_str(arg)) {
      write("Must supply an argument.");
      return 1;
   }
   sscanf(arg, "%d", i);
   set_ac(i);
   write("Set armor class to " + i);

   return 1;
}

int wear_hook(object player) {
   if (query_mortal(player)) {
      player->write("You are not allowed to wear the hauberk of the " +
         "immortals.");
   }
   return !query_mortal(player);
}
