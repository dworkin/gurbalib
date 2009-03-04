inherit ROOM;

void setup( void ) {
  set_brief( "%^BLUE%^Fighters Guild%^RESET%^" );
  set_long( "You are standing in the entrance to the Fighters Guild. There are weapons and armor of different kinds on the walls. On the floor there is a thick red carpet, and you can make out some discolored spots here and there. The carpet looks like it's getting pretty old." );
  set_exits( ([ 
	       "south" : "/domains/gurba/rooms/gelmir3",
	       "north" : "/domains/gurba/guilds/fighter/main",
  ]) );

  set_objects( ([
		 "/domains/gurba/guilds/fighter/master" : 1 
		 ])
	       );

  add_item( "carpet", "rug", "red carpet", "The carpet isn't just discolored here and there, it's stained with blood." );
}

void do_listen( void ) {
  write( "To the north you hear metal clanging against metal, and the odd cry in agony. Once in a while you hear muffled laughter as well." );
}
