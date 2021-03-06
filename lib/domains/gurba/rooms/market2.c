inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "MarketStreet" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Market Street" );
   set_long( "The street grows narrow here, confining the huge crowd that habitually populates Market Street in an even smaller space. People are yelling and shoving, children are crying, and music is blaring. All in all, the conditions are likely not great for one's health. Market Street continues towards the western gate in one direction, and toward the town square in the other." );
   
   set_exits( ([ 
		  "east" : "/domains/gurba/rooms/market1",
		  "west" : "/domains/gurba/rooms/market3",
		  ]) );
   
}