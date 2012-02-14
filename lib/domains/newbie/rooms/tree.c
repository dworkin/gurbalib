inherit ROOM;

void setup( void ) {
   add_area( "newbie" );

   set_brief( "%^MAGENTA%^North end of field.%^RESET%^" );
   set_long( "You are in a large open field, next to an old dead tree. " +
      " To the South you see a road leading to a city.  There is an odd " +
      "hole in a hill to the north.");

   set_exits( ([ 
      "south" : "/domains/required/rooms/start",
   ]) );

   set_objects( ([ 
      "/domains/newbie/objects/sign" : 1,
      "/domains/newbie/objects/tree" : 1,
   ]) );

   add_item("hole", "A funny hole in the ground.  You might be able to " +
      "squeeze into it.");

  add_room_command("squeeze", "enter_hole");
  add_room_command("break", "break_branch");
}

int enter_hole(string arg) {
   string dest;

   if (arg == "hole") {
      if( this_player()->is_completed_quest("NewbieVille")) {
         write("The hole is too small for you to enter it.\n");
      } else {
         dest = "/domains/newbie/rooms/entrance";
         this_player()->query_environment()->tell_room( this_player(),
            this_player()->query_Name() + " enters the hole.\n");
         write("You enter the hole.\n");
         this_player()->move(dest);
         this_player()->query_environment()->tell_room( this_player(),
            this_player()->query_Name() + 
            " pops out of the hole.\n");
         this_player()->do_look(0);
      }
      return 1;
   } else {
     write("squeeze what?\n");  // maybe remove this line? 
                              // So you can try other enter commands...
     return 0;
   }
}

int break_branch(string str) {
   object obj;
   if (str == "branch") {
      if( this_player()->is_completed_quest("NewbieVille")) {
         write("There are no branches left on the tree that you can reach.\n");
      } else {
         this_player()->query_environment()->tell_room( this_player(),
            this_player()->query_Name() + 
            " breaks a branch off of the tree.\n");
         write("You break a branch off of the tree.\n");
         obj = clone_object("/domains/newbie/objects/stick.c");
	 obj->move(this_player());
         obj->setup();
      }
   } else {
      write("Break what?\n");
   }
}
