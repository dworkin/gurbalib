inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "GelmirRoad" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Gelmir Road" );
   set_long( "Gelmir Road is one of the busier streets in the city of Gurba.  Inhabitants of the town and visitors from abroad pass by in both directions, attending to their various errands and business.  To the east lies the entrance to the Fighter's Guild.  Further to the west you can see the town square." );
   
   set_exits( ([ 
		  "east" : "/domains/gurba/rooms/gelmir3",
		  "west" : "/domains/gurba/rooms/gelmir1",
		  ]) );
   
}