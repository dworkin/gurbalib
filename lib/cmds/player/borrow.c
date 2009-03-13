void main( string str ) {

  if( !str || str == "" ) {
    this_player()->write( "Borrow what?" );
    return;
  }

  if( !this_environment()->is_storage() ) {
    this_player()->write( "Perhaps you should try borrowing your item from a storage?" );
    return;
  }

  this_environment()->borrow_object( str );

}
