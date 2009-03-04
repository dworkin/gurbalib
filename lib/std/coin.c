/* Created by Fudge */

inherit OBJECT;
inherit M_GETTABLE;

string text;

void create( void ) {
  ::create( );
  set_id( "sign" );
  set_long( "Your average wooden sign." );
  set_in_room_desc( "A wooden sign is standing here." );
  set_gettable( 0 );
}

void set_message( string message ) {
  text = message;
}

int can_read( object who ) {
  return( 1 );
}

int do_read( object who ) {
  write( text );
  return( 1 );
}
rrency = str;
}

void set_amount( int amt ) {
  amount = amt;
  if( amt == 1 ) {
    set_in_room_desc( "One " + currency );
    set_long( "A lonely " + currency + "." );
  } else if( amt < 10 ) {
    set_in_room_desc( "A couple of " + currency + "s" );
    set_long( "A couple of " + currency + "s." );
  } else if( amt < 20 ) {
    set_in_room_desc( "A few " + currency + "s" );
    set_long( "A few " + currency + "s. About 15." );
  } else if( amt < 40 ) {
    set_in_room_desc( "Some " + currency + "s" );
    set_long( "Some " + currency + "s. About 30." );
  } else if( amt < 80 ) {
    set_in_room_desc( "Many " + currency + "s" );
    set_long( "Many " + currency + "s. About 50." );
  } else if( amt < 150 ) {
    set_in_room_desc( "Lots of " + currency + "s" );
    set_long( "Lots of " + currency + "s. About 100." );
  } else {
    set_in_room_desc( "A huge pile of " + currency + "s" );
    set_long( "A huge pile of " + currency + "s. More than you'd care to count." );
  }
}