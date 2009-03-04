int cur_hp;
int max_hp;

void create( void ) {
  cur_hp = 1;
  max_hp = 1;
}

void increase_hp( int hp ) {
  cur_hp += hp;
  if( cur_hp >= max_hp ) {
    cur_hp = max_hp;
    this_object()->message( "%^BLUE%^You are fully healed.%^RESET%^" );
  }
}

void decrease_hp( int hp ) {
  cur_hp -= hp;
  if( cur_hp < 0 )
    cur_hp = 0;
}

void set_max_hp( int hp ) {
  max_hp = hp;
}

void set_hp( int hp ) {
  if( hp > max_hp )
    hp = max_hp;

  cur_hp = hp;
}

int query_max_hp( void ) {
  return( max_hp );
}

int query_hp( void ) {
  return( cur_hp );
}

int is_alive( void ) {
  if( cur_hp > 0 )
    return( 1 );
  return( 0 );
}

int is_dead( void ) {
  if( cur_hp <= 0 )
    return( 1 );
  return( 0 );
}