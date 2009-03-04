/* Simple command to show all objects in the room 
 * Fudge
 */

void main( string arg ) {
  object *objs;
  int i;

  write( "Scanning \"" + object_name( this_environment() ) + "\":" );
  objs = this_environment()->query_inventory();
  for( i = 0; i < sizeof( objs ); i ++ ) {
    write( "\"" + object_name(objs[i]) + "\"" );
  }
}
