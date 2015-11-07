#include "../domain.h"

inherit "/std/object";

void setup(void) {
   set_id("rules");
   set_short("Go rules");
   set_long("A list of the rules for playing Go.\n" +
      "There are 5 rules.\n" +
      "Do 'rule #', to read a rule number.");

   add_action("do_rule", "rule");
}

string get_rules1() {
   return "There are two players, black and white.\n" +
      "They take turns, playing one stone each.\n" +
      "Black starts with one or more stones, depending on the handicap.\n\n" +
      "The stones are played in a matrix on the intersections.\n" +
      "It is allowed to play on the outer border.\n\n" +
      "The normal game size is 19 x 19 (that is 18 x 18 squares),\n" +
      "but the game can also be played on smaller boards.";
}

string get_rules2() {
   return "The winner, is the player with the highest score on the board\n" +
      "when the game ends.\n\n" +
      "The game ends when both players have passed.\n\n";
      "The score is the number of stones + number of surrounded empty " +
      "intersections.";
}

string get_rules3() {
   return "A group is defined as one or more stones of the same colour,\n" +
      "that are connected along the lines.\n" + 
      "Stones besides each other are connected, but stones positioned " +
      "diagonally\nfrom each other are not.\n\n" + 
      "A liberty is an empty space beside a stone.\n" +
      "Again, an empty space diagonally from a stone does not count.\n\n" +
      "The liberties of a group, are the number of liberties that a group " +
      "have.\n" +
      "Liberties can be shared by more than one group.";
}

string get_rules4() {
   return "If a stone is played so that the last liberty of an enemy group\n" +
      " is removed, then all stones in that enemy group are removed.\n\n" +
      "If a stone is played so that the last liberty of a group of the same " +
      "colour\n" +
      "is removed, then it is an illegal move.";
}

string get_rules5() {
   return "If the position of the board is a repeat of an earlier position,\n" +
      "then the last move was illegal.";
}

int do_rule(string str) {
   if (str == "1") {
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " reads rule #" + str + "\n");
      write(get_rules1());
   } else if (str == "2") {
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " reads rule #" + str + "\n");
      write(get_rules2()); 
   } else if (str == "3") {
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " reads rule #" + str + "\n");
      write(get_rules3());
   } else if (str == "4") {
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " reads rule #" + str + "\n");
      write(get_rules4());
   } else if (str == "5") {
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " reads rule #" + str + "\n");
      write(get_rules5());
   } else {
      write("No rule: " + str + "\n");
      write("Try looking at the rules.\n");
   }
   return 1;
}
