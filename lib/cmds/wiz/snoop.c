void usage() {
  write("Usage: snoop [-h] PLAYER\n");
  write("Snoop on player: PLAYER.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  if( !str || str == "" ) {
    int i;
    object *pSnooping;
    
    pSnooping = this_player()->query_snooping();
    if( pSnooping && sizeof( pSnooping ) > 0 ) { 
      this_player()->message( "You are snooping:" );
      for( i = 0; i < sizeof( pSnooping ); i++ ) {
	this_player()->message( capitalize( pSnooping[i]->query_name() ) );
      }
    } else {
      this_player()->message( "You are snooping no one." );
    }
  } (sscanf(str, "-%s",str)) {
     usage();
     return;
  } else {
    object pPlayer;

    pPlayer = USER_D->find_player( str );

    if( pPlayer == this_player() ) {
      this_player()->message( "You can't snoop yourself." );
      return;
    }

    if( !pPlayer ) {
      this_player()->message( "That player isn't here now." );
    } else {
      if( this_player()->is_snooping( pPlayer ) ) {
	this_player()->remove_snooping( pPlayer );
	pPlayer->remove_snoopee( this_player() );
      } else {
	int i;
	object *pSnooping;

	pSnooping = pPlayer->query_snooping();
	if( pSnooping && sizeof( pSnooping ) > 0 ) {
	  for( i = 0; i < sizeof( pSnooping ); i++ ) {
	    if( pSnooping[i]->query_name() == this_player()->query_name() ) {
	      this_player()->message( "He's already snooping you." );
	      return;
	    }
	  }
	}
	this_player()->add_snooping( pPlayer );
	pPlayer->add_snoopee( this_player() );
      }
    }
  }
}
