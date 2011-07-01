inherit ROOM;

void setup( void ) {
  set_brief( "%^MAGENTA%^Just outside of town.%^RESET%^" );
  set_long( "You are sitting just outside of town." );
  set_exits( ([ 
	       "out" : "/domains/gurba/rooms/square_center",
  ]) );
}

// XXX Make it so this meshes better with the town of gurba but
//     still easy for someone to remove the town if they want to and
//     start fresh
