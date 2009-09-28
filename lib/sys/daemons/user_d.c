#define AUTH_DATA "/sys/daemons/auth_data"
#define CACHE_INTERVAL 300
#define AUTH_DATA_DIR "/sys/daemons/data/users/"

static mapping users;
static mapping cache;
static object * pool;
int data_version;

int logout( string name );
object find_user( string name );


static void secure() {
  if( previous_program(1) != USER && !require_priv( "system" ) ) {
    error( "Access denied." );
  }
}

static void save_me() {
  unguarded( "save_object", "/sys/daemons/data/user_d.o" );
}

static void restore_me() {
  unguarded( "restore_object", "/sys/daemons/data/user_d.o" );
}

/*
 * If there are any data objects (clones) around, destruct them.
 *
 */
static void cleanup() {
  object c, n;

  c = find_object( AUTH_DATA );
  if( !c ) {
    return;
  }

  c = c->next_clone();

  while( c ) {
    n = c->next_clone();
    if( pool ) {
      pool -= ({ c });
    }
    destruct_object( c );
    c = n;
  }
}

static void create() {
  object * u;
  int i,sz;

  cache = ([ ]);
  pool = ({ });
  restore_me();

  if( !data_version ) {
    call_out( "convert_users", 0 );
  }

  users = ([ ]);

  u = users();

  for( i = 0, sz = sizeof( u ); i < sz; i++ ) {
    if( u[i]->query_name() && u[i]<-USER ) {
      users[u[i]->query_name()] = u[i];
    }
  }

  call_out( "clean_cache", CACHE_INTERVAL );
  cleanup();
}

static object get_data_ob( string name ) {
  object ob;

  ob = cache[name];

  if( ob ) {
    return ob;
  }

  if( !sizeof( pool ) ) {
    pool += ({ clone_object( AUTH_DATA ) });
  }

  ob = pool[0];
  pool = pool[1..];

  if( ob->load( name ) ) {
    cache[name] = ob;
    return ob;
  } else {
    if( sizeof( pool ) < 10 ) {
      pool += ({ ob });
    } else {
      destruct_object( ob );
    }
  }
}

static void clean_cache() {
  int i, sz;
  string * names;

  names = map_indices( cache );
  
  for( i = 0, sz = sizeof( names ); i < sz; i++ ) {
    if( !USER_D->find_user( names[i] ) ) {
      logout( names[i] );
    }
  }

  call_out( "clean_cache", CACHE_INTERVAL );
}

int logout( string name ) {
  object ob;

  secure();

  ob = cache[name];

  if( ob ) {
    if( sizeof( pool ) < 10 ) {
      pool += ({ ob });
    } else {
      destruct_object( ob );
    }
    return 1;
  } else {
    return 0;
  }
}

int login( string name, string secret ) {
  object data;

  secure();

  data = get_data_ob( name );

  if( !data ) {
    return 0;
  }

  return data->test( secret );
}

int user_exists( string name ) {
  return file_exists( AUTH_DATA_DIR + name[0..0] + "/" + name + ".o" ) == 1;
}

static int _new_user( string name, string secret ) {
  object ob;

  if( sizeof( pool ) ) {
    ob = pool[0];
    pool = pool[1..];
  } else {
    ob = clone_object( AUTH_DATA );
  }

  ob->set_name( name );
  ob->set_pass( secret );
  return 1;
}

int new_user( string name, string secret ) {
  secure();

  return unguarded( "_new_user", name, secret );
}

void delete_user( string name ) {
  object u,p;

  if( !require_priv( "system" ) ) {
    error( "Access denied." );
  }

  if( u = find_user( name ) ) {
    p = u->query_player();
    destruct_object( u );
    if( p ) {
      destruct_object( p );
    }
  }

  unguarded( "remove_file", AUTH_DATA_DIR + name[0..0] + "/" + name + ".o" );
  unguarded( "remove_file", "/data/players/" + name + ".o" );
}

static void convert_users() {
  string * names;
  int i,sz;
  object c;

  names = get_dir("/data/players/*.o")[0];
  c = clone_object( AUTH_DATA );

  rlimits( MAX_DEPTH; -1 ) {
    for( i = 0, sz = sizeof( names ); i < sz; i++ ) {
      string n;

      sscanf( names[i], "%s.o", n );
      c->convert_user( n );
    }
  }
  data_version = 1;
  save_me();
  destruct_object( c );
}

static void destructing() {
  cleanup();
}

void user_online( string name, object user ) {
  users += ([ name : user ]);
}

void user_offline( string name, object user ) {
  users[name] = nil;
  unguarded( "logout", name );
}

object *query_users( void ) {
  return( map_values( users ) );
}

string *query_user_names( void ) {
  return( map_indices( users ) );
}

object find_user( string name ) {
  string *names;
  int i, sz;
  int found;

  found = 0;
  names = map_indices( users );
  for( i = 0, sz = sizeof(names); i < sz; i++ ) {
    if( name == names[i] ) {
      found = 1;
      break;
    }
  }

  if( found == 1 ) 
    return( users[name] );
  else 
    return( nil );
}

object find_player( string name ) {
  object ob;
  ob = find_user( lowercase(name) );
  if( ob )
    return( ob->query_player() );
  return( ob );
}

object *query_players( void ) {
  object *usr;
  int i,sz;
  object *players;

  usr = query_users();

  players = ({ });

  for ( i = 0, sz = sizeof(usr); i < sz; i++ ) {
    players += ({ usr[i]->query_player() });
  }
  return players;
}


object *query_wizards( void ) {
  object *usr;
  int i,sz;
  object *wizards;

  usr = query_users();

  wizards = ({ });

  for ( i = 0, sz = sizeof(usr); i < sz; i++ ) {
    if (query_wizard(usr[i]->query_player()->query_name()) > 0) {
      wizards += ({ usr[i]->query_player() });
    }
  }
  return wizards;
}
	    
int valid_player_name(string str) {
  return !catch(parse_string("valid=/[a-zA-Z][a-zA-Z0-9]+/ name: valid", str));
}

int player_exists( string str ) {
  return unguarded( "file_exists", "/data/players/"+str+".o" ) > 0;
}

void upgraded() {
  object * u;
  int i,sz;

  if(!users) {
    users = ([ ]);
    u = users();
    for( i = 0, sz = sizeof( u ); i < sz; i++ ) {
      if( u[i]->query_name() && u[i]<-USER ) {
        users[u[i]->query_name()] = u[i];
      }
    }
  }
}
