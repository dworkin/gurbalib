#include "../../../domain.h"

inherit DIR + "/lib/room";

int cmd_break_jar(string str) {
   object brain;
   
   if (empty_str(str) || str != "jar") {
      write("Break what, precisely?");
      return 0;
   }
   if (this_object()->present("brain guard")) {
      write("The brain's guard prevents you!");
      return 1;
   }
   brain = present("brain");
   if (brain) {
      write("You smash the jar with the brain and it explodes in a shower " +
         "sparks. The brain falls to the ground with a soft, wet thud.");
      tell_room(this_player(), "The jar with the brain and it explodes in " +
         "a shower of sparks. The brain falls to the ground with " + 
         "a soft, wet thud.");
      brain->destruct();
      add_object(NOKICLIFFS_BRAIN, 1);
   } else {
      write("There is no jar to break.");
   }
   return 1;
}

int cmd_smash_jar(string str) {
   return cmd_break_jar(str);
}

int cmd_shatter_jar(string str) {
   return cmd_break_jar(str);
}

void setup(void) {
   set_short("A large cave chamber in the Noki Cliffs");
   set_long("The chamber here is huge. You get the feeling that this is " +
      "an ancient place of magic where wondrous (and strange) things occur. " +
      "But it also feels like it might have been forgotten about a very long " +
      "time ago as there doesn't seem to be much left from those ancient " +
      "days.");
   set_objects(NOKICLIFFS_BRAIN_IN_JAR);
   set_exits((["south" : DIR + "/rooms/cliffs/cave/puzzle_chamber.c"]));
   add_action("cmd_break_jar", "break");
   add_action("cmd_smash_jar", "smash");
   add_action("cmd_shatter_jar", "shatter");
}
