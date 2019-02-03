#include "../../domain.h"

inherit NOKICLIFFS_VENDOR;

#define INTERVAL 30

static int     count;
static string *acts;

void setup(void) {
   set_name("silverspun");
   add_ids("apothecarist");
   set_gender("female");
   set_race("elf");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE);
   set_short("Silverspun the apothecarist");
   set_long("Silverspun is old and wise. Everything that she sells " +
      "she produces herself. She produces garlic because " +
      "vampires hate garlic. She slices fresh fruit because " +
      "nothing is tastier and will give you an energy boost. " +
      "Her granola is second to none and is useful for healing " +
      "the body as well as recovering spent mental energy.");
   add_item(DIR + "/obj/garlic", 2);
   add_item(DIR + "/obj/fresh_fruit", 8);
   add_item(DIR + "/obj/granola", 4);
   count = 0;
   acts = ({  "smile" });
}

void vendor_transfer_hook(object sold_what, object sold_to) {
   sold_what->start_spoiling();
}

void do_extra_actions(void) {
   if (is_fighting()) {
      return;
   }

   if (count++ > INTERVAL) {
      if (random(2)) {
         respond("emote smiles pleasantly.");
         count = 0;
      }
   }
}

void outside_message(string str) {
   str = lowercase(ANSI_D->strip_colors(str));
}
