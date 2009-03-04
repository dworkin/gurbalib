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
      pSnoopees[i]->message( "%^RED%^[" + capitalize( this_object()->query_name() ) + "] %^RESET%^" + lines[j] );
    }
  }
}

void add_snoopee( object pPlayer ) {
  if( !pSnoopees )
    pSnoopees = ({ });
  this_object()->message( "%^RED%^You are now beeing snooped by " + capitalize( pPlayer->query_name() ) + ".%^RESET%^" );
  pSnoopees += ({ pPlayer });
}

void remove_snoopee( object pPlayer ) {
  if( !pSnoopees ) 
    pSnoopees = ({ });
  pSnoopees -= ({ pPlayer });
  this_object()->message( "%^RED%^You are no longer beeing snooped by " + capitalize( pPlayer->query_name() ) + ".%^RESET%^" );
}

void add_snooping( object pPlayer ) {
  if( !pSnooping )
    pSnooping = ({ });
  pSnooping += ({ pPlayer });
  this_player()->message( "%^RED%^You are now snooping " + capitalize( pPlayer->query_name() ) + ".%^RESET%^" );
}

void remove_snooping( object pPlayer ) {
  if( !pSnooping )
    pSnooping = ({ });
  pSnooping -= ({ pPlayer });
  this_player()->message( "%^RED%^You are no longer snooping " + capitalize( pPlayer->query_name() ) + ".%^RESET%^" );
}
