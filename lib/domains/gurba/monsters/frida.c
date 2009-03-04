inherit M_VENDOR;

void setup( void ) {
  set_name( "frida" );
  set_proper_name( "Frida" );
  set_gender( 2 );
  add_id( "shopkeeper", "merchant" );
  set_in_room_desc( "Frida, the florist" );
  set_long( "She has a long brown pony tail, and a daisy stuck behind an ear." );
  set_race( "human" );

  set_restock_delay( 7200 );

  add_item( "/domains/gurba/objects/roses", 9 );
}

