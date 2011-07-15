inherit ROOM;

void setup( void ) {
  set_brief( "%^MAGENTA%^A narrow passage.%^RESET%^" );
  set_long( "You are in a small tunnel.  It was a tight squeeze to get in " +
     "here.");
  set_exits( ([ 
	       "north" : "/domains/required/rooms/entrance",
	       "south" : "/domains/required/rooms/fighting",
  ]) );
}

