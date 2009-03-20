inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "BorderWalk" );
   add_area( "BorderWalkWest" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Border Walk - West" );
   set_long( "You are on the Border Walk, the long and narrow street which surrounds the town of Gurba in a large rectangle. It runs along the inside edge of the stone town wall, which at the moment lies to your west. To the south a turn in the road can be seen, while to the north the walk heads toward the western town gate." );
   
   set_exits( ([ 
		  "south" : "/domains/gurba/rooms/border_west1",
		  "north" : "/domains/gurba/rooms/border_west3",
		  ]) );
   
}