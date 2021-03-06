inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "BorderWalk" );
   add_area( "BorderWalkEast" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Border Walk - East" );
   set_long( "You are on the Border Walk, the long and narrow street which surrounds the town of Gurba in a large rectangle. It runs along the inside edge of the stone town wall, which at the moment lies to your east. The walk runs to the south from here. Immediately to the north you can see the impressive stone archway of the eastern city gate." );
   
   set_exits( ([ 
		  "south" : "/domains/gurba/rooms/border_east3",
		  "north" : "/domains/gurba/rooms/gate_east",
		  ]) );
   
}