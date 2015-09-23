#include "../domain.h"

inherit "/std/room";

int current_problem, starts_thinking, problem_value;
object solved_by, wrong_by;

void setup(void) {
   add_area("2.4.5");

   set_short("The local pub");
   set_long("You can order drinks here.");

   set_objects(
      DIR + "/monsters/barkeep.c",
      DIR + "/monsters/goplayer.c",
      DIR + "/obj/go.c",
      "/domains/required/objects/mer_sign.c"
   );

   add_exit("west", DIR + "/rooms/yard.c");
}

/* XXX More work here go functions... */

int show_problem() {
   if (current_problem > 2) {
      if (present("player")) {
         write("The player looks tired.\n");
      } else {
         write("The board is in disarray and the player is no longer here.\n");
      }
      return 1;
   }

   this_environment()->tell_room(this_player(), this_player()->query_Name() +
      " examines the go problem.\n");

   if (current_problem == 0) {
      write("5|.......\n" +
         "4|.......\n" +
         "3|@@@@@..\n" +
         "2|OOOO@..\n" +
         "1|...O@..\n" +
         " --------\n" +
         "  abcdefg\n" +
         "\nIt is black ('@') to play.\n");
      return 1;
   } else if (current_problem == 1) {
      write("7|.......\n" +
         "6|.......\n" +
         "5|@@@....\n" +
         "4|OOO@@..\n" +
         "3|O.OO@..\n" +
         "2|...O@..\n" +
         "1|..OO@..\n" +
         " --------\n" +
         "  abcdefg\n" +
         "\nIt is black ('@') to play.\n");
      return 1;
   } else if (current_problem == 2) {
      write("5|..........\n" +
         "4|...@@@@@..\n" +
         "3|@@@.O...@.\n" +
         "2|@OO@OOOO@.\n" +
         "1|@OO.O...@.\n" +
         " -----------\n" +
         "  abcdefg\n" +
         "\nIt is white ('O') to play.\n");
      return 1;
   } else {
      write("The go player does not want to be disturbed any more.\n");
   }
   return 1;
}

int make_move() {
   int i;

   if (solved_by) {
      i = current_problem + 1;
      say("The go player says: Right ! That works !\n" +
         "He immediately plays out a new problem.\n");
      solved_by->message("You feel that you have gained some experience.\n");

      solved_by->increase_expr(problem_value);

      solved_by = nil;
      current_problem += 1;
   }
   if (wrong_by) {
      tell_room(this_object(), "The go player says: No, that doesn't work.\n");
      tell_room(this_object(), "He sinks back into his deep thought.\n");
      wrong_by = nil;
   }
}
