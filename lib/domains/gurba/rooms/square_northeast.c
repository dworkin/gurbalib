inherit OUTDOOR_ROOM;

void setup( void ) {
   add_area( "Gurba" );
   add_area( "GurbaSquare" );
   add_area( "GurbaOutdoor" );
   
   set_brief( "Gurba Town Square - Northeast" );
   set_long( "Not much seems to be going on here in the northeastern corner of the square.  The occasional merchant and street performer wanders by, but the real activity seems to be located to the south and west of here.  A clothing shop to the east seems to be doing fairly steady business." );
   
   set_exits( ([ 
		  "west" : "/domains/gurba/rooms/square_north", 
		  "south" : "/domains/gurba/rooms/square_east",
		  "southwest" : "/domains/gurba/rooms/square_center",
		  ]) );
   
}