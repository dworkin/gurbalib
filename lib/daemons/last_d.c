mapping last;

static void restore_me( void );
static void save_me( void );

void create( void ) {
  last = ([ ]);
  restore_me();
}

static void restore_me( void ) {
  unguarded( "restore_object", "/daemons/data/last.o" );

}

static void save_me( void ) {
  unguarded( "save_object", "/daemons/data/last.o" );
}

void add_entry( string name, int on ) {
  string ip;

  if( on ) {
    last[name] = "[%^CYAN%^" + ctime( time() ) + "%^RESET%^] %^GREEN%^" + capitalize( name ) + "%^RESET%^ logs on from %^BOLD%^" + query_ip_number( USER_D->find_user( name ) ) + "%^RESET%^\n";
  } else {
    ip = query_ip_number( USER_D->find_user( name ) );
    if(!ip) ip = "<LD>";
    last[name] = "[%^CYAN%^" + ctime( time() ) + "%^RESET%^] %^GREEN%^" + capitalize( name ) + "%^RESET%^ logged off from %^BOLD%^" + ip + "%^RESET%^\n";
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
