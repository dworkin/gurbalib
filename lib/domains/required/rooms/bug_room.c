inherit "/std/room";

#define DIR "/domains/required"

void setup(void) {
   add_area("required");

   set_short("Bug room");
   set_long("The room contains a huge and fluffy chair, since wizards " +
      "spend a lot of time in this room reading the bug reports from the " +
      "players. ");

   add_item("chair", "The chair is really worn down, and has a big 'dent' " +
      "in it which looks like a perfect match for someone's butt.");

   set_objects(DIR + "/objects/bug_board");

   set_exits(([
      "out" : STARTING_ROOM, 
   ]));
}
