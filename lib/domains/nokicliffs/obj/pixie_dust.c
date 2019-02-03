#include "../domain.h"

inherit "/std/object";

private void pixie_curse(object target) {
   string str;
   object controller;
   str = "$N $vinhale some pixie dust from a " +
      "small bag and $vblink several times " +
      "rapidly. The bag explodes into a shower " +
      "of brilliant multi-colored glitter.";
   target->targeted_action(str, target);
   move(NOKICLIFFS_VOID);
   controller = find_object(PIXIES_CONTROLLER);
   if (!controller) {
      controller = compile_object(PIXIES_CONTROLLER);
   }
   controller->curse(target->query_Name(), 60*60, 100);
}

private int pixie_dust_command(string str) {
   if (!empty_str(str) && str == "pixie dust") {
      pixie_curse(this_player());
      return 1;
   }
   return 0;
}

int inhale_cmd(string str) {
   return pixie_dust_command(str);
}
 
int sniff_cmd(string str) {
   return pixie_dust_command(str);
}

int snort_cmd(string str) {
   return pixie_dust_command(str);
}

private void add_actions(void) {
   add_action("inhale_cmd", "inhale");
   add_action("sniff_cmd", "sniff");
   add_action("snort_cmd", "snort");
}

void setup(void) {
   set_id("pixie dust");
   add_ids("dust", "bag of pixie dust",
      "small bag of pixie dust");
   set_short("A small bag of pixie dust");
   set_long("A small bag of pixie dust. " +
      "According to legend strange things " +
      "happen to those who inhale pixie dust.");
   set_gettable(1);
   set_value(5);
   set_weight(1);
   add_actions();
}
