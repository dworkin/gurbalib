inherit ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "GelmirRoad" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Gelmir Road" );
   set_long( "Gelmir Road widens here as it approaches the town square to the west.  A constant stream of people are coming and going from the square, and a loud commotion can be heard.  Further to the east sits the entrance to a large and ornate building." );
   
   set_exits( ([ 
		  "east" : "/domains/gurba/rooms/gelmir2",
		  "west" : "/domains/gurba/rooms/square_east",
		  ]) );
   
}
