#include "../domain.h"

inherit "/std/object";

string beads_owner_name;

void setup() {
   set_id("beads");
   set_short("A string of dimensional beads");
   set_long("Some dimensional beads. You can 'activate' them.");
   set_gettable(1);
   set_weight(1);
   set_value(0);
   add_action("activate_cmd", "activate");
}

void update_short() {
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
      write("You can 'activate oak grove' pocket dimension.");
      write("You can 'activate doomspire' pocket dimension.");
      return 1;
   }

   if (lowercase(str) == "oak grove") {
      this_player()->move(NOKICLIFFS_OAK_GROVE_START);
      this_player()->do_look(0);
   } else if (lowercase(str) == "doomspire") {
      this_player()->move(NOKICLIFFS_DOOMSPIRE_START);
      this_player()->do_look(0);
	} else if (lowercase(str) == "abbey of law") {
		this_player()->move(NOKICLIFFS_ABBEY_START);
		this_player()->do_look(0);
	} else if (lowercase(str) == "den of chaos") {
		this_player()->move(NOKICLIFFS_DEN_START);
		this_player()->do_look(0);
	} else if (lowercase(str) == "hall of balance") {
		this_player()->move(NOKICLIFFS_HALL_START);
		this_player()->do_look(0);
   } else {
      write("Your beads cannot activate that pocket dimension.");
   }
   return 1;
}

int post_drop() {
   this_object()->query_environment()->tell_room(nil,
      "The beads shatter as they hit the ground.");
   this_object()->destruct();
   return 1;
}
