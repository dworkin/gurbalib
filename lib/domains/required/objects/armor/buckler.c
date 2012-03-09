inherit SHIELD;

void setup( void ) {
  set_id( "buckler" );
  set_adj( "small", "round" );
  set_long( "A buckler." );
  set_in_room_desc( "A buckler." );
  set_gettable( 1 );

  set_ac( 1 );

  set_wield_type( "single" );
  set_wield_message( "$N $vequip $p $o." );
  set_unwield_message( "$N $vremove $p $o." );
  set_value( 1 );
  set_size( 10 );
}
