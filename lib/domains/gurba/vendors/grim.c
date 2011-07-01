inherit M_VENDOR;

void setup( void ) {
  set_name( "grim" );
  set_proper_name( "Grim" );
  set_gender( "male" );
  add_id( "shopkeeper", "merchant" );
  set_in_room_desc( "Grim, the Armsmaster" );
  set_long( "A stubby dwarf with bulging muscles. He's covered with sweat, probably from standing in front of his forge.." );
  set_race( "dwarf" );

  set_restock_delay( 7200 );

  add_item( "/domains/gurba/objects/weapons/sword", 9 );
  add_item( "/domains/required/objects/weapons/short_sword", 9 );
}

