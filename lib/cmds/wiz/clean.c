/* A small command to clear out all the objects in a room
 *
 * Fudge
 */

void main( string arg ) {
  object *objs;
  int i;

  objs = this_environment()->query_inventory();
  for( i = 0; i < sizeof( objs ); i++ ) {
    if( !objs[i]->is_player() ) {
      objs[i]->destruct();
    }
  }
  this_player()->simple_action( "$N $vclean the room.", nil );
}
