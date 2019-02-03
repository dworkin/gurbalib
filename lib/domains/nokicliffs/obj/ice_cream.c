#include "../domain.h"

inherit NOKICLIFFS_ROOT;

int do_eat(void) {
   this_player()->targeted_action("$N $veat $P ice cream with a " +
      "smile.", this_object());
   this_object()->destruct();
   return 1;
}

string get_warn_short(void) {
   return "Ice cream (melting)";
}

string get_warn_long(void) {
   return "The ice cream is melting!";
}

string get_warn_message(void) {
   return "The ice cream is melting!";
}

string get_spoil_message(void) {
   return "The ice cream has not been eaten soon enough and it has " +
      "melted away and exists only as drip marks on the ground.";
}

void spoil_hook(void) {
   this_object()->destruct();
}

void setup(void) {
   ::setup();
   set_id("ice cream");
   set_short("Ice cream");
   set_long("The ice cream is your favorite flavor. Enjoy!");
   set_eatable(1);
   set_value(1);
   set_weight(1);
}
