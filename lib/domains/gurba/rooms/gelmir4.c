inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "GurbaOutdoor" );
   add_area( "GelmirRoad" );
   
   set_brief( "Gelmir Road" );
   set_long( "This is one of the busier parts of one of the town's busiest streets. To the east lies the eastern gate of the town, while to the west sits the intimidatingly large dome of the Fighter's Guild. Large crowds of people wander past, some headed toward the town square in the distance to the west." );
   
   set_exits( ([ 
		  "east" : "/domains/gurba/rooms/gate_east",
		  "west" : "/domains/gurba/rooms/gelmir3",
		  ]) );
   
}