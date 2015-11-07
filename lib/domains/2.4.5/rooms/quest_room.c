#include "../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Room of quests");
   set_long("This was the room of quests.\n" +
      "It has been replaced by or own quest system.\n" +
      "What follows are old outdated instructions.  For current info talk to " +
      "an admin and look at the help for the following commands:\n" +
      "\tquests, questadm, check\n" +
      "Begin old instructions:  Every wizard can make at most " +
      "one quest.  When he has made a quest, he should have it approved " +
      "by an arch wizard.  When it is approved, put a permanent object " +
      "in this room, which has as short description the name of the " +
      "wizard.  All objects in this room will be checked when a player " +
      "wants to become a wizard. The player must have solved ALL quests.  " +
      "To mark that a quest is solved, call 'set_quest(\"name\")' " +
      "in the player object. The objects must all accept the id 'quest' " +
      "and the name of the wizard. The objects must also define a " +
      "function hint(), that should return a message giving a hint of " +
      "where to start the quest. Note that players never can come here.  " +
      "set_quest(str) will return 1 if this is the first time it was " +
      "solved by this player, otherwise 0.");

   add_exit("south", DIR + "/rooms/wiz_hall.c");
}

