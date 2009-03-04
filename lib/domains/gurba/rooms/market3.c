
inherit ROOM;

void setup( void ) {
  set_brief( "%^MAGENTA%^Market Boulevard%^RESET%^" );
  set_long( "This is the market street in Gurba. Further to the east lies the town square. To the north is the first National Bank of Gurba, southwards you can find a cozy little restaurant called 'Chez Mario'. There is a small sign standing here." );
  set_exits( ([ 
	       "west" : "/domains/gurba/rooms/market4", 
	       "east" : "/domains/gurba/rooms/market2",
               "north" : "/domains/gurba/rooms/bank",
               "south" : "/domains/gurba/rooms/restaurant",
  ]) );

  add_item( "road", "The road here is paved with cobblestones due to all the traffic that runs through here." );
  add_item( "cobblestone", "cobblestones", "cobble", "stones", "The stones are small quadratic stones laid down side by side." );
  add_item( "sign", "There is a piece of paper nailed to the sign it says: 'Playing tonight at Mario's, The Rolling Stones'." );
  set_objects( ([ 
  ]) );

}

void do_listen( object player ) {
  write( "You hear the bustling sound of trade, money, haggling and merchants having it off at each other." );
}

