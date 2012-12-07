#include "../domain.h"
inherit ROOM;

void setup(void) {
   add_area("newbie");

   set_brief("North end of the field");
   set_long("You are in a large open field, next to an old dead tree. " +
      " To the South you see a road leading to a city.  There is an odd " +
      "hole in a hill to the north.");

   set_exits(([
      "south" : STARTING_ROOM,
      "hole" : DIR + "/rooms/entrance",
   ]));

   set_objects(([
      DIR + "/obj/sign" : 1, 
      DIR + "/obj/tree" : 1,
   ]));

   add_item("hole", "A funny hole in the ground.  You might be able to " +
      "squeeze into it.");

   add_room_command("squeeze", "enter_hole");
   add_room_command("break", "break_branch");
}

int break_branch(string str) {
   object obj;
   if (str == "branch") {
      if (this_player()->is_completed_quest("NewbieVille")) {
	 write("There are no branches left on the tree that you can reach.\n");
      } else {
	 this_player()->query_environment()->tell_room(this_player(),
	    this_player()->query_Name() +
	    " breaks a branch off of the tree.\n");
	 write("You break a branch off of the tree.\n");
	 obj = clone_object(DIR + "/obj/stick.c");
	 obj->move(this_player());
	 obj->setup();
      }
      return 1;
   } else {
      return 0;
   }
}
