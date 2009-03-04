string *banished_names;

void create( void ) {
  mixed *list;
  list = get_dir( "/data/banished/*" );
  banished_names = list[0];
}


string *query_banished_names( void ) {
  return( banished_names );
}

int is_banished( string name ) {
  if( member_array(name, banished_names) != -1 )
    return( 1 );
  return( 0 );
}


void banish_name (string str) {
   write_file( "/data/banished/"+str, ctime( time() ) + "\tby:  "  +
      this_user()->query_name() +"\n" );
   create();
}   

void unbanish_name (string str) {
   remove_file( "/data/banished/"+str);
   create();
}   

