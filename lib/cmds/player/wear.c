void main( string str ) {
  object obj;
  object worn;

  obj = this_player()->find_object( lowercase( str ) );
  if( !obj ) {
    write( "Maybe you should get one first?" );
    return;
  }
  if( !obj->is_wearable() ) {
    write( "You can't wear that." );
    return;
  }

  worn = this_player()->query_slot( obj->query_slot() );
  if( worn ) {
    write("You're already wearing a " + worn->query_id() + "." );
    return;
  }
  
  this_player()->do_wear( obj );
  this_player()->targetted_action( obj->query_wear_message(), nil, obj );
}