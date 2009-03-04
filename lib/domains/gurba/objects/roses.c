inherit OBJECT;
inherit M_GETTABLE;
inherit M_VALUABLE;

void setup( void ) {
  set_id( "boquet", "flowers" );
  set_adj( "rose", "red" );
  set_long( "A boquet of red roses." );
  set_in_room_desc( "Someone has left a boquet of roses here." );
  set_gettable( 1 );
  set_value( 10 );
}
