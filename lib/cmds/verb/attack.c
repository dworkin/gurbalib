mixed *query_verb_info( void ) {
  return( ({ "", "LIV" }) );
}

mixed can_attack( void ) {
  return( "Attack who?" );
}

mixed can_attack_liv( object liv ) {
  return( 1 );
}

mixed do_attack_liv( object liv ) {
  this_player()->targetted_action( "$N $vattack $t.", liv );
  this_player()->attack( liv );
}
