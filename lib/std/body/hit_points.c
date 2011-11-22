int cur_hp;
int max_hp;
int cur_mana;
int max_mana;
int cur_end;
int max_end;

void create( void ) {
  cur_hp = 1;
  max_hp = 1;
  cur_mana = 1;
  max_mana = 1;
  cur_end = 1;
  max_end = 1;
}

void increase_hp( int hp ) {
  cur_hp += hp;
  if( cur_hp >= max_hp ) {
    cur_hp = max_hp;
    this_object()->message( "%^BLUE%^You are fully healed.%^RESET%^" );
  }
}

void increase_mana( int mana ) {
  cur_mana += mana;
  if( cur_mana >= max_mana ) {
    cur_mana = max_mana;
  }
}

void increase_end( int end ) {
  cur_end += end;
  if( cur_end >= max_end ) {
    cur_end = max_end;
  }
}

void decrease_hp( int hp ) {
  cur_hp -= hp;
  if( cur_hp < 0 ) cur_hp = 0;
}

void decrease_mana( int mana ) {
  cur_mana -= mana;
  if( cur_mana < 0 ) cur_mana = 0;
}

void decrease_end( int end ) {
  cur_end -= end;
  if( cur_end < 0 ) cur_end = 0;
}

void set_max_hp( int hp ) {
  max_hp = hp;
}

void set_max_mana( int mana ) {
  max_mana = mana;
}

void set_max_end( int end ) {
  max_end = end;
}

void set_hp( int hp ) {
  if( hp > max_hp ) hp = max_hp;
  cur_hp = hp;
}

void set_mana( int mana ) {
  if( mana > max_mana ) mana = max_mana;
  cur_mana = mana;
}

void set_end( int end ) {
  if( end > max_end ) end = max_end;
  cur_end = end;
}

int query_max_hp( void ) {
  return( max_hp );
}

int query_max_mana( void ) {
  return( max_mana );
}

int query_max_end( void ) {
  return( max_end );
}

int query_hp( void ) {
  return( cur_hp );
}

int query_mana( void ) {
  return( cur_mana );
}

int query_end( void ) {
  return( cur_end );
}

string query_status( void ) {
  int x,max, t;

  max = this_object()->query_max_hp();
  x = this_object()->query_hp();

  if (x == max) return "in peak physical condition.";
  if (max < 5) {
    if (x < max/2) return "nocking on deaths door.";
    return "wounded.";
  } else {
    t = max / 5;
    x = x / t;

    switch (x) {
      case 5:
        return "in peak physical condition.";
        break;
      case 4:
        return "bairly scratched.";
        break;
      case 3:
        return "lightly wounded.";
        break;
      case 2:
        return "wounded.";
        break;
      case 1:
        return "is in really bad shape.";
        break;
      default:
        return "nocking on deaths door.";
        break;
    }
  }
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
