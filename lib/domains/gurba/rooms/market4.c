
inherit ROOM;

void setup( void ) {
  set_area( "Gurba" );
  set_brief( "%^MAGENTA%^Market Boulevard%^RESET%^" );
  set_long( "This is where Market boulevard meets Six-pence Avenue, and ends. to the east you will reach the town square. Northwards you will find the University of Gurba. South lies the park." );
  set_exits( ([ 
	       "east" : "/domains/gurba/rooms/market3",
               "north" : "/domains/gurba/rooms/sixp1",
  ]) );

  add_item( "road", "The road here is paved with cobblestones due to all the traffic that runs through here. However you can se that traffic has not been that hard on the road here." );
  add_item( "cobblestone", "cobblestones", "cobble", "stones", "The stones are small quadratic stones laid down side by side." );
   set_objects( ([ 
  ]) );

}

void do_listen( object player ) {
  write( "You hear the muffled sound of trade, money, haggling and merchants having it off at each other." );
}

