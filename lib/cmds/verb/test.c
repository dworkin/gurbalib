string *query_verb_info( ) {
  return( ({ "", "OBJ", "LIV", "OBJ with LIV" }) );
}

int can_test() {
  write( "can_test() returns 1" );
  return( 1 );
}

int can_test_obj( object obj ) {
  return( 1 );
}

int can_test_liv( object liv ) {
  return( 1 );
}

int can_test_obj_with_liv( object obj, string s, object liv ) {
  return( 1 );
}

void do_test() {
  write( "You test." );
}

void do_test_obj( object obj ) {
  write( "You test object :" + obj->query_id() );
}

void do_test_liv( object obj ) {
  write( "You test liv :" + obj->query_id() );
}

void do_test_obj_with_liv( object obj, string s, object liv ) {
  write( "You test obj with liv : " + obj->query_id() + ", " + liv->query_id() );
}

