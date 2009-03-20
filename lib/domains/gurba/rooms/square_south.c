inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "GurbaSquare" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Gurba Town Square - South" );
   set_long( "The south side of Gurba's town square is given over to public speaking. Anyone may speak here on any topic, and there are always several individuals who take advantage of the open-minded atmosphere to give speeches on their personal causes and concerns. Small audiences stand around, occasionally clapping or booing at the speakers' words. Weller Avenue leaves south out of the square from here." );
   
   set_exits( ([ 
		  "east" : "/domains/gurba/rooms/square_southeast", 
		  "west" : "/domains/gurba/rooms/square_southwest",
		  "north" : "/domains/gurba/rooms/square_center",
		  "south" : "/domains/gurba/rooms/weller1",
		  ]) );
   
   add_item( "speakers", "At the moment, you see one man talking in a strident fashion about religion, and another townsman proclaiming his concerns about the town's crime rate." );
   
}