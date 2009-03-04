void main( string str ) {
  object ob;

  ob = this_player()->find_object( str );

  if( !ob ) {
    write( "You can't seem to find the " + lowercase( str ) + "." );
    return;
  }

  if( !this_environment()->is_storage() ) {
    this_player()->write( "Perhaps you should try storing your item in a storage?" );
    return;
  }

  this_environment()->store_object( ob );

}