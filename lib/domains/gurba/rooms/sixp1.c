
inherit ROOM;

void setup( void ) {
  set_area( "Gurba" );
  set_brief( "%^YELLOW%^Six-pence Avenue%^RESET%^" );
  set_long( "Six-pence Avenue continues up north towards the University. Southwards it meets with Market Boulevard, and then carries on towards the park." );
  set_exits( ([ 
	       "north" : "/domains/gurba/rooms/sixp2",
               "south" : "/domains/gurba/rooms/market4",
  ]) );

  add_item( "road", "The road here looks like your average dusty third world road. It needs to be paved, but construction hasn't come that far yet. " );
  add_item( "dust", "Yup! thats dust all right." );
   set_objects( ([ 
  ]) );

}

void do_listen( object player ) {
  write( "It is very quiet here, the only thing you can hear is the wind blowing." );
}

