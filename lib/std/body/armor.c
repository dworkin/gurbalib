/* Created by Fudge at Mon Mar  2 19:41:42 1998 */

static mapping equipment;

void do_wear( object ob ) {
  if( !equipment ) {
    equipment = ([ ]);
  }
  equipment[ob->query_slot()] = ob;
  ob->set_worn( 1 );
}

void do_remove( object ob ) {
  if( !equipment ) {
    equipment = ([ ]);
  }
  equipment[ob->query_slot()] = 0;
  ob->set_worn( 0 );
}

object query_slot( string slot ) {
  if( !equipment ) {
    equipment = ([ ]);
  }
  return( equipment[slot] );
}

object *query_equipment( void ) {
  return( map_values( equipment ) );
}
