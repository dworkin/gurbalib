static object *pSnoopees;
static object *pSnooping;

void create( void ) {
  pSnoopees = ({ });
  pSnooping = ({ });
}

int is_snooped( void ) {
  if( !pSnoopees )
    pSnoopees = ({ });
  if( sizeof( pSnoopees ) > 0 ) {
    return( 1 );
  }
  return( 0 );
}

int is_snooping( object pPlayer ) {
  int i;
  if( !pSnooping )
    pSnooping = ({ });
  for( i = 0; i < sizeof( pSnooping ); i++ ) {
    if( pSnooping[i] == pPlayer )
      return( 1 );
  }
  return( 0 );
}

object *query_snooping( void ) {
  if( !pSnooping )
    pSnooping = ({ });
  return( pSnooping );
}

object *query_snoopees( void ) {
  if( !pSnoopees )
    pSnoopees = ({ });
  return( pSnoopees );
}

void do_snoop( string str ) {
  int i,j;
  string *lines;

  lines = explode( str, "\n" );

  for( j = 0; j < sizeof( lines ); j ++ ) {
    for( i = 0; i < sizeof( pSnoopees ); i++ ) {
      pSnoopees[i]->message( "%^RED%^[" + this_object()->query_Name() + "] %^RESET%^" + lines[j] );
    }
  }
}

void add_snoopee( object pPlayer ) {
  if( !pSnoopees )
    pSnoopees = ({ });
  this_object()->message( "%^RED%^You are now beeing snooped by " + 
     pPlayer->query_Name() + ".%^RESET%^" );
  pSnoopees += ({ pPlayer });
}

void remove_snoopee( object pPlayer ) {
  if( !pSnoopees ) 
    pSnoopees = ({ });
  pSnoopees -= ({ pPlayer });
  this_object()->message( "%^RED%^You are no longer beeing snooped by " + 
     pPlayer->query_Name() + ".%^RESET%^" );
}

void add_snooping( object pPlayer ) {
  if( !pSnooping )
    pSnooping = ({ });
  pSnooping += ({ pPlayer });
  this_player()->message( "%^RED%^You are now snooping " + 
     pPlayer->query_Name() + ".%^RESET%^" );
}

void remove_snooping( object pPlayer ) {
  if( !pSnooping )
    pSnooping = ({ });
  pSnooping -= ({ pPlayer });
  this_player()->message( "%^RED%^You are no longer snooping " + 
     pPlayer->query_Name() + ".%^RESET%^" );
}
