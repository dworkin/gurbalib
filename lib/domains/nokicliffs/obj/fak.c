#include "../domain.h"
#define HEALING_AMT (15 + random(15))

inherit "/std/object";
inherit NOKICLIFFS_HEALING_LIB;
inherit DIR + "/lib/reloadable";

string query_short(void) {
   return "A first aid kit [" + query_charges() + " use" +
         (query_charges() != 1 ? "s": "") + " remain]";
}

string query_long(void) {
   int i;
   i = query_charges();

   return "A first kit with enough supplies for " + i +
      " more use" + (i != 1 ? "s" : "") + ". You can " +
      "'bandage' yourself or a comrade to help recovery " +
      "from physical injury. It may be reloaded by any " +
      "a suitable medical clinic nurse or doctor; when " +
      "you buy a first aid kit, you are charged only the " +
      "cost to refill your kit.";
}

void setup(void) {
   set_id("first aid kit");
   add_ids("kit", "fak");
   set_gettable(1);
   set_value(50);
   set_weight(1);
   set_max_charges(10);
   set_charges(10);
   add_action("bandage_cmd", "bandage");
}

int bandage_cmd(string str) {
   if (query_charges() < 1) {
      write("Your first aid kit is out of supplies.");
      return 1;
   }
   set_doctor(this_player());
   if (empty_str(str)) {
      set_patient(this_player());
   } else {
      set_patient((str == "me" || str == "self" || str == "myself") ?
         this_player() :
         this_player()->query_environment()->present(str));
   }
   if (!query_patient()) {
      write("Bandage who?");
      return 1;
   }
   if (!hp_needed()) {
      show_healing_message("$N $veye $p first aid kit and " +
         " $vshow concern for $T.");
      return 1;
   }
   recover_hp(HEALING_AMT, "$N $vapply a first aid kit to $T.");
   decrement_charges();
   if (query_charges() < 1) {
      write("You have used all the supplies in your first aid kit.");
   }
   return 1;
}
