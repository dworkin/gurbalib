
inherit ROOM;

void setup( void ) {
  add_area( "Gurba" );
  set_brief( "%^MAGENTA%^Market Boulevard%^RESET%^" );
  set_long( "You are further up in the market street of Gurba. A bit to the east you see the town square. There is a statue of Albert Von Turnip here. To the north you will find the weaponshop, and to the south the armorshop." );
  set_exits( ([ 
	       "west" : "/domains/gurba/rooms/market3", 
	       "east" : "/domains/gurba/rooms/market1",
               "north" : "/domains/gurba/rooms/weapshop",
               "south" : "/domains/gurba/rooms/armorshop",
  ]) );

  add_item( "road", "The road here is paved with cobblestones due to all the traffic that runs through here." );
  add_item( "cobblestone", "cobblestones", "cobble", "stones", "The stones are small quadratic stones laid down side by side." );
  add_item( "statue", "Albert", "albert", "The statue is nicely cut in jet black rock. It was put here to honour Albert Von Turnip, the founder of the Order of the Golden Turnip." ),
  set_objects( ([ 
  ]) );

}

void do_listen( object player ) {
  write( "You hear the bustling sound of trade, money, haggling and merchants having it off at each other." );
}

