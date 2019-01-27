#include "../../domain.h"

inherit "/std/armors/helmet";
inherit DIR + "/lib/wizards_hat/teleport";
inherit DIR + "/lib/wizards_hat/light";

string query_long(void) {
   string str;

   str = ::query_long();
   if (query_worn()) {
      str += " It fits very well, and since it is thick and well " +
         "made it probably offers some protection against blows.";
   } else {
      str += " It is thick and well made. On the inside you a label. " +
         "The label says: ....";
   }
   if (query_lit()) {
      str += " The wizard's hat is glowing brightly.";
   }

   return str;
}

nomask int hat_stat_cmd(string str) {
   object obj;

   obj = get_teleport_destination();
   if (!nilp(obj)) {
      write("Teleport destination: " + obj->query_short());
      if (query_wizard(this_player())) {
         write("\t" + teleport_destination);
      }
      return 1;
   }
   write("Teleport destination has not yet been set.");
   return 1;
}

private void add_actions(void) {
   add_action("hat_stat_cmd", "hatstat");
   add_action("set_destination_cmd", "memorator");
   add_action("teleport_cmd", "hoppla");
   add_action("light_cmd", "lux");
   add_action("unlight_cmd", "finito");
}

void setup(void) {
   ::setup();
   set_id("hat", "wizard's hat", "blue velvet wizard's hat");
   set_adj("magical", "blue", "velvet");
   set_short("A blue velvet wizard's hat");
   set_long("This hat is made of blue velvet with stars and moons " +
      "in silver. It is high and pointed, quite obviously a " +
      "wizard's hat.");
   set_weight(1);
   set_size(6);
   add_actions();
}
