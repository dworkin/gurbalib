inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "BorderWalk" );
   add_area( "BorderWalkSouth" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Border Walk - South" );
   set_long( "You are on the Border Walk, the long and narrow street which surrounds the town of Gurba in a large rectangle. It runs along the inside edge of the stone town wall, which at the moment lies to your south. To the west there seems to be a turn in the road, while to the east the road heads through a small business district." );
   
   set_exits( ([ 
		  "west" : "/domains/gurba/rooms/border_south1",
		  "east" : "/domains/gurba/rooms/border_south3",
		  ]) );
   
}