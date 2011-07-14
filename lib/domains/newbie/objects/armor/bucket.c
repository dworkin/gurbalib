inherit ARMOR;
inherit M_VALUABLE;

void setup( void ) {
  set_id( "bucket" );
  set_adj( "small", "round" );
  set_long( "A bucket, it looks like you could wear it as a helmet if you " +
     "were really desperate." );
  set_in_room_desc( "A bucket." );
  set_gettable( 1 );

  set_ac( 1 );

  set_slot("head");
  set_value( 1 );
  set_size( 10 );
}
