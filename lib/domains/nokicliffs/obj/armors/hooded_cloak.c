#include "../../domain.h"

inherit DIR + "/lib/armor";

#define DEFAULT_CLOAK_AC 2
#define POWERED_CLOAK_AC 10

static int cloak_powered;

int is_cloak_powered(void) {
   return cloak_powered;
}

string query_short(void) {
   string str;

   str = ::query_short();

   if (cloak_powered) {
      str += " %^BOLD%^%^YELLOW%^[cloak power on]%^RESET%^";
   }

   return str;
}

void after_wear(object player) {
   if (!player || !query_worn()) {
      remove_call_out(cloak_powered);
      cloak_powered = 0;
      set_ac(DEFAULT_CLOAK_AC);
   }
}

void after_unwear(object player, string cmd) {
   ::after_unwear(player, cmd);

   if (player && cloak_powered) {
      player->message("The cloak powers down.");
   }

   remove_call_out(cloak_powered);
   cloak_powered = 0;
   set_ac(DEFAULT_CLOAK_AC);
}

void cloak_power_off(object obj) {
   if (cloak_powered) {
      obj->message("The cloak powers down.");
   }

   remove_call_out(cloak_powered);
   cloak_powered = 0;
   set_ac(DEFAULT_CLOAK_AC);
}

int do_cloak_power(string str) {
   if (empty_str(str) || str != "power on") {
      write("Are you trying to switch the 'cloak power on'?");
      return 1;
   }

   if (!query_worn()) {
      write("You have to wear it first.");
      return 1;
   }

   if (cloak_powered) {
      write("It's already powered on.");
      return 1;
   }

   if (this_player()->query_mana() < 30) {
      write("You do not have enough mana.");
      return 1;
   }

   set_ac(POWERED_CLOAK_AC);
   this_player()->decrease_mana(30);
   cloak_powered = call_out("cloak_power_off", 120, this_player());
   this_player()->simple_action("$N $vactivate the cloak.", this_player());

   return 1;
}

void setup(void) {
   set_id("cloak");
   add_ids("hooded cloak");
   set_adj("hooded");
   set_short("A hooded cloak");
   set_long("This black hooded cloak is somewhat tattered " +
      "at the bottom from years of use. Do not be fooled, " +
      "however, as this is not your standard issue hooded " +
      "cloak.");
   set_ultra_light();
   set_ac(DEFAULT_CLOAK_AC);

   add_action("do_cloak_power", "cloak");
   cloak_powered = 0;
}
