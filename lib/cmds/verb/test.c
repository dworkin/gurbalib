mixed *query_verb_info( void ) {
  return( ({ "", "OBJ", "LIV", "OBJ with LIV" }) );
}

mixed can_test( void ) {
  write( "can_test() returns 1" );
  return( 1 );
}

mixed can_test_obj( object obj ) {
  return( 1 );
}

mixed can_test_liv( object liv ) {
  return( 1 );
}

mixed can_test_obj_with_liv( object *obj, string s, object liv ) {
  return( 1 );
}

mixed do_test( void ) {
  write( "You test." );
}

mixed do_test_obj( object obj ) {
  write( "You test object :" + obj->query_id() );
}

mixed do_test_liv( object obj ) {
  write( "You test liv :" + obj->query_id() );
}

mixed do_test_obj_with_liv( object obj, string s, object liv ) {
  write( "You test obj with liv : " + obj->query_id() + ", " + liv->query_id() );
}

