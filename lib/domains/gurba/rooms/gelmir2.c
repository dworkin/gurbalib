inherit ROOM;

void setup( void ) {
  set_area( "Gurba" );
  set_brief( "%^CYAN%^Gelmir Road%^RESET%^" );
  set_long( "You are now a short distance from the town square. It's getting harder to see what's going on over there. To the west is a pub, and to the east you see the Fighters Guild." );
  set_exits( ([ 
	       "west"  : "/domains/gurba/rooms/gelmir1",
	       "east"  : "/domains/gurba/rooms/gelmir3",
  ]) );

  add_item( "road", "path", "floor", "street", "The road is in a fairly good condition. Some of the rocks used to pave the road have lost their square shape, or are chipped in any way." );
}
