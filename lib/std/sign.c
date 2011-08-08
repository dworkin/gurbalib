/* Created by Fudge */

inherit OBJECT;
inherit M_GETTABLE;
inherit M_READABLE;

void create( void ) {
  ::create( );
  set_id( "sign" );
  set_long( "Your average wooden sign.  It has some writing on it." );
  set_in_room_desc( "A wooden sign." );
  set_gettable( 0 );
}


