mapping last;

void restore_me( void );
void save_me( void );

void create( void ) {
  last = ([ ]);
  restore_me();
}

void restore_me( void ) {
  restore_object( "/daemons/data/last.o" );

}

void save_me( void ) {
  save_object( "/daemons/data/last.o" );
}

void add_entry( string name, int on ) {
  if( on ) {
    last[name] = "[%^CYAN%^" + ctime( time() ) + "%^RESET%^] %^GREEN%^" + capitalize( name ) + "%^RESET%^ logs on from %^BOLD%^" + query_ip_number( USER_D->find_user( name ) ) + "%^RESET%^\n";
  } else {
    last[name] = "[%^CYAN%^" + ctime( time() ) + "%^RESET%^] %^GREEN%^" + capitalize( name ) + "%^RESET%^ logged off from %^BOLD%^" + query_ip_number( USER_D->find_user( name ) ) + "%^RESET%^\n";
  } 
  save_me();
}

string query_entry( string name ) {
  return( last[name] );
}

string query_list( void ) {
  string *players;
  string msg;
  int i;

  msg = "";
  players = map_indices( last );
  for( i = 0; i < sizeof( players ); i++ ) {
    msg += query_entry( players[i] );
  }
  return msg;
}
