inherit ROOM;

void setup( void ) {
  set_brief( "%^MAGENTA%^A large open field.%^RESET%^" );
  set_long( "You are in a large open field.  To the north you see some " +
     "sort of sign.  To the west you see the ancient city of gurba.");
  set_exits( ([ 
	       "north" : "/domains/newbie/rooms/hole_in_the_ground",
	       "west" : "/domains/gurba/rooms/gate_east",
  ]) );
}

