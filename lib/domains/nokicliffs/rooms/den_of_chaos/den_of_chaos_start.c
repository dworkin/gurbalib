#include "../../domain.h"

inherit DIR + "/lib/room";

void setup(void) {
   set_light(0);
   set_short("The Den of Chaos in a pocket dimension");
   set_long("You are standing at the entrance to the Den of Chaos. " +
      "You are somewhere deep underground, perhaps even in one from " +
      "lower planes. This place does not give you a bad feeling or a " +
      "good feeling. No; instead it gives you a chaotic feeling which is " +
      "unsettling. The urge to create balance is strong. You can " +
      "the Den of Chaos or go deeper into it by going east. " +
      "You can 'leave' the pocket dimension. " +
      "Ideally it will return you to the room you " +
      "arrived from; if it is not found, then you " +
      "go to the base camp.");

   set_exits(([
      "east": DIR + "/rooms/den_of_chaos/passage.c",
      "leave": NOKICLIFFS_BASE_CAMP
   ]));
}
