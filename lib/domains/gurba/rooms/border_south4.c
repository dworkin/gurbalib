inherit ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "BorderWalk" );
   add_area( "BorderWalkSouth" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Border Walk - South" );
   set_long( "You are on the Border Walk, the long and narrow street which surrounds the town of Gurba in a large rectangle. It runs along the inside edge of the stone town wall, which at the moment lies to your south. The road passes here through a small and relatively quiet business district. The road continues to the east and west." );
   
   set_exits( ([ 
		  "east" : "/domains/gurba/rooms/border_south5",
		  "west" : "/domains/gurba/rooms/border_south3",
		  ]) );
   
}
