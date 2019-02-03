#include "../domain.h"

inherit "/std/object";

string beads_owner_name;

void setup(void) {
   set_id("beads");
   set_short("A string of dimensional beads");
   set_long("Some dimensional beads. You can 'activate' them. " +
      "The enchantment on these beads, when activated, teleport you " +
      "to small explorable pocket dimensions. These pocket dimensions " +
      "alien places but you will find some degree of familiarity among " +
      "them. These beads belong to you now.");
   set_gettable(1);
   set_weight(1);
   set_value(20);
   add_action("activate_cmd", "activate");
}

void update_short(void) {
   setup();
   set_short(beads_owner_name + "'s string of dimensional beads");
}

void set_owner_name(object player) {
   beads_owner_name = player->query_Name();
}

int activate_cmd(string str) {
   write("These beads can open pocket dimensions.");
   if (this_player()->is_player() &&
      beads_owner_name != this_player()->query_Name()) {
      write("Unfortunately this is not your string of beads.");
      return 1;
   }
   if (empty_str(str)) {
      write("You can 'activate' the following pocket dimensions: " +
         "\n\tabbey\n" +
         "\n\tden of chaos\n" +
         "\n\tdoomspire\n" +
         "\n\thall of balance\n" +
         "\n\toak grove\n" +
         "\n\tmurky mists\n" +
         "For instance, to activate the den of " +
         "chaos pocket dimension, use command: " +
         "activate den of chaos");
      return 1;
   }

   if (lowercase(str) == "doomspire") {
      this_player()->move(NOKICLIFFS_DOOMSPIRE_START);
   } else if (lowercase(str) == "oak grove") {
      this_player()->move(NOKICLIFFS_OAK_GROVE);
   } else if (lowercase(str) == "abbey") {
      this_player()->move(NOKICLIFFS_ABBEY_START);
   } else if (lowercase(str) == "den of chaos") {
      this_player()->move(NOKICLIFFS_DEN_START);
   } else if (lowercase(str) == "hall of balance") {
      this_player()->move(NOKICLIFFS_HALL_START);
   } else if (lowercase(str) == "murky mists") {
      this_player()->move(NOKICLIFFS_MURKY_MISTS_START);
   } else {
      write("Your beads cannot activate that pocket dimension.");
      return 1;
   }
   this_player()->do_look(this_environment());
   return 1;
}

int post_drop(void) {
   this_object()->query_environment()->tell_room(nil,
      "The beads shatter as they hit the ground.");
   this_object()->destruct();
   return 1;
}
