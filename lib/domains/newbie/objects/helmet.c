inherit ARMOR;
inherit M_VALUABLE;

void setup( void ) {
  set_id( "helmet" );
  set_adj( "small", "round" );
  set_long( "A small rusty helmet, it looks like it has seen better days.  " +
     "You would have to be really desperate to put this thing on." );
  set_in_room_desc( "A small rusty helmet." );
  set_gettable( 1 );

  set_ac( 1 );

  set_slot("head");
  set_value( 1 );
  set_size( 10 );
}
