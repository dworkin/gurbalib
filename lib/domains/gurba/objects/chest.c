inherit CONTAINER;
inherit M_OPENABLE;

void setup( void ) {
  set_id( "chest" );
  set_adj( "wooden", "big" );
  set_long( "A big wooden chest." );
  set_objects( ([ 
		 "/domains/gurba/objects/small_rock" : 1,
		 "/domains/gurba/objects/large_rock" : 1,
		 ]) );
  set_open_state( 0 );
}
