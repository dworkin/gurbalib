inherit ROOM;

void setup( void ) {
  add_area( "newbie" );

  set_brief( "%^MAGENTA%^end of the tunnel.%^RESET%^" );
  set_long( "You are at the end of a small tunnel.  The room is brightly " +
     "colored and everything in the room direct's your attention " +
     "towards a large red button.");

  set_exits( ([ 
	       "north" : "/domains/newbie/rooms/drinkme",
	       "out" : "/domains/newbie/rooms/tree",
  ]) );

  add_item("button", "A giant red BUTTON!\nIt is glowing and says PRESS ME!");
  add_room_command("push", "do_push");
}

int do_push(string arg) {
   if (arg == "button") {
      if( this_player()->is_completed_quest("NewbieVille")) {
          write("The button is already depressed.\n");
      } else {
         this_player()->add_completed_quest("NewbieVille");
         this_player()->increase_expr(200);
         write("Congradulations!!! You have just completed the NewbieVille " +
           "Quest which earns you 200 exp!\n");
      }
   } else {
      write("Push what?");
   }
}
