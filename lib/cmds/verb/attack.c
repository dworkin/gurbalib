string *query_verb_info() {
  return( ({ "", "LIV" }) );
}

int can_attack() {
  return 1;
}

int can_attack_liv( object liv ) {
  return( 1 );
}

void do_attack() {
  write( "Attack who?" );
  return;
  }

void do_attack_liv( object liv ) {
  this_player()->targetted_action( "$N $vattack $t.", liv );
  this_player()->attack( liv );
}
