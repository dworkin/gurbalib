#include "../domain.h"

inherit "/std/room";

int current_problem;

void setup(void) {
   add_area("2.4.5");

   set_short("The local pub");
   set_long("You can order drinks here.");

   set_objects(
      DIR + "/monsters/barkeep.c",
      DIR + "/monsters/goplayer.c",
      DIR + "/obj/top_list.c",
      DIR + "/obj/go.c",
      "/domains/required/objects/mer_sign.c"
   );

   add_exit("west", DIR + "/rooms/yard.c");

   add_item("puzzle", "#show_problem");
   add_item("game", "#show_problem");
   add_item("problem", "#show_problem");

   current_problem = 0;
}

string show_problem() {
   string result;
   if (current_problem > 2) {
      if (present("player")) {
         result = "The player looks tired.\n";
      } else {
         result = "The board is in disarray and the player is no " +
            "longer here.\n";
      }
      return result;
   }

   result = "You look at the go problem.\n";

   if (current_problem == 0) {
      result += "5|.......\n" +
         "4|.......\n" +
         "3|@@@@@..\n" +
         "2|OOOO@..\n" +
         "1|...O@..\n" +
         " --------\n" +
         "  abcdefg\n" +
         "\nIt is black's('@') turn to play.\n";
   } else if (current_problem == 1) {
      result += "7|.......\n" +
         "6|.......\n" +
         "5|@@@....\n" +
         "4|OOO@@..\n" +
         "3|O.OO@..\n" +
         "2|...O@..\n" +
         "1|..OO@..\n" +
         " --------\n" +
         "  abcdefg\n" +
         "\nIt is black's('@') turn to play.\n";
   } else if (current_problem == 2) {
      result += "5|..........\n" +
         "4|...@@@@@..\n" +
         "3|@@@.O...@.\n" +
         "2|@OO@OOOO@.\n" +
         "1|@OO.O...@.\n" +
         " -----------\n" +
         "  abcdefg\n" +
         "\nIt is white's('O') turn to play.\n";
   } else {
      result += "The go player does not want to be disturbed any more.\n";
   }
   return result;
}

int query_current_problem() {
   return current_problem;
}

int set_current_problem(int i) {
   current_problem = i;
}
