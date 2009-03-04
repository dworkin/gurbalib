void main( string str ) {
  int i;
  object *obj;

  obj = this_environment()->query_inventory();

  for( i=0; i < sizeof( obj ); i++ ) {
    if( obj[i]->is_fighting() )
      obj[i]->halt_fight();
  }
  this_player()->write( "Combat halted.\n" );
}
