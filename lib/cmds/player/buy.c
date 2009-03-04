/* Created by Fudge */

void main( string str ) {
  object *objs;
  int i;

  if( str == "" ) {
    write( "Buy what?" );
    return;
  }

  objs = this_environment()->query_inventory();
  for( i = 0; i < sizeof( objs ); i++ ) {
    if( objs[i]->is_vendor() == 1 ) {
      /* Found the shopkeeper */

      objs[i]->do_sell( this_player(), str );
      return;

    }
  }

  write( "Buy from whom?" );
}
