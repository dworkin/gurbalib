static mapping verbs;
static string *names;

void create( void ) {
  mixed *list;
  object verb;

  int i;

  verbs = ([ ]);

  list = get_dir( "/cmds/verb/*.c" );
  names = list[0];

  for( i = 0; i < sizeof( names ); i++ ) {
    names[i] = names[i][.. (strlen( names[i] )-3)];
    verb = clone_object( "/cmds/verb/" + names[i] );
    verbs[names[i]] = verb;
  }
}

string *query_verbs( void ) {
  return( names );
}

int is_verb( string verb ) {
  if( member_array( verb, map_indices( verbs ) ) != -1 )
    return( 1 );
  return( 0 );
}
                       