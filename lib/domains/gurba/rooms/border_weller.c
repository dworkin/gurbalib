inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "BorderWalk" );
   add_area( "BorderWalkSouth" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Intersection of Border Walk/Weller Avenue" );
   set_long( "Here, the long rectangular Border Walk crosses the end of Weller Avenue, the home of the more affluent members of Gurba's populace, which leads to the north from here. Large trees and elaborate stonework mark the entrance to this district. The Border Walk continues to the east and west." );
   
   set_exits( ([ 
		  "east" : "/domains/gurba/rooms/border_south6",
		  "west" : "/domains/gurba/rooms/border_south5",
		  "north" : "/domains/gurba/rooms/weller3",
		  ]) );
   
}