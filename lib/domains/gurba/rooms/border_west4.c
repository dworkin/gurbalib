inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "BorderWalk" );
   add_area( "BorderWalkWest" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Border Walk - West" );
   set_long( "You are on the Border Walk, the long and narrow street which surrounds the town of Gurba in a large rectangle. It runs along the inside edge of the stone town wall, which at the moment lies to your west. The walk runs to the south from here. Immediately to the north you can see the impressive stone archway of the western city gate." );
   
   set_exits( ([ 
		  "south" : "/domains/gurba/rooms/border_west3",
		  "north" : "/domains/gurba/rooms/gate_west",
		  ]) );
   
}