inherit ROOM;

void setup( void ) {
  set_brief( "%^MAGENTA%^end of the tunnel.%^RESET%^" );
  set_long( "You are at the end of a small tunnel.  There is a large " +
     "red button here.");
  set_exits( ([ 
	       "north" : "/domains/newbie/rooms/fighting",
	       "out" : "/domains/newbie/rooms/tree",
  ]) );
  add_item("button" "A giant red BUTTON!");
}

