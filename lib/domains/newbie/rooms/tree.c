#include "../domain.h"

inherit "/std/room";

#define FILE DIR + "/rooms/entrance.c"

void setup(void) {
   add_area("newbie");

   set_short("North end of the field");
   set_long("You are in a large open field, next to an old dead tree. " +
      " To the South you see a road leading to a city.  There is an odd " +
      "hole in a hill to the east.");

   set_exits(([
      "south" : STARTING_ROOM,
      "east" : "#enter_hole",
   ]));

   set_objects(
      DIR + "/obj/sign", 
      DIR + "/obj/tree"
   );

   add_item("hole", "A funny hole in the ground.  You might be able to " +
      "squeeze into it.");

   add_action("break_branch", "break");
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

void enter_hole(void) {
   object obj;

   if (this_player()->is_completed_quest("NewbieVille")) {
      write("You don't seem to fit through the hole anymore.");
      this_object()->tell_room(this_player(), this_player()->query_Name() + 
         " tries to squeeze through the hole but can not seem to " +
         "fit through it.");
      return;
   } else {
      obj = find_object(FILE);
      if (!obj) {
         obj = compile_object(FILE);
         if (!obj) {
            write("Error in loading destination.\n");
            return;
         }
         obj->setup();
         obj->setup_mudlib();
      }
      if (this_player()->move(obj)) {
         write("You wriggle through the hole.");
         this_object()->tell_room(this_player(),
            this_player()->query_Name() + " squeezes through the hole.\n");
	 this_player()->do_look(0);
      }
   }
   return;
}
