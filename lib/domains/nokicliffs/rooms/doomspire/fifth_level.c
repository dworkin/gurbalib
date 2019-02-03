#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   string glyphs_str;

   glyphs_str = "The glyphs cannot be read by you, but " +
         "sometimes glow with magical energy, perhaps " +
         "an indication that someone somewhere has met " +
         "their doom. With some heavy concentration, " +
         "think you may have worked out the name 'Angmar' " +
         "within the glyphs.";

   set_short("Doomspire top level");
   set_long("You are on top of the Doomspire. " +
      "You dare not look out over the doomscape. " +
      "You notice that you are standing on a large " +
      "magical symbol. There are various hieroglyphs " +
      "that you do not understand, and probably never " +
      "will. Sometimes the glyphs flicker "+
      "and glow with magical energy.");

   add_item("doomscape", "You dare not look at such a place.");
   add_item("glyphs", glyphs_str);
   add_item("hierglyphs", glyphs_str);
   add_item("energy", glyphs_str);
   add_item("magical energy", glyphs_str);

   set_exits(([
      "down" : DIR + "/rooms/doomspire/fourth_level_end.c"
   ]));
}
