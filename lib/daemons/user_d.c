static mapping users;

void create( void ) {
  users = ([ ]);
}

void add_user( string name, object user ) {
  users += ([ name : user ]);
}

void remove_user( string name, object user ) {
  users[name] = nil;
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
    if (SECURE_D->query_wiz(usr[i]->query_player()->query_name()) > 0) {
      wizards += ({ usr[i]->query_player() });
    }
  }
  return wizards;
}
	    
int valid_player_name(string str) {
  return !catch(parse_string("valid=/[a-zA-Z][a-zA-Z0-9]+/ name: valid", str));
}

