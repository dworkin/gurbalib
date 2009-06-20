
mixed *did;

static void save_me( void ) {
  unguarded( "save_object", "/daemons/data/did_d.o" );
}

static void restore_me( void ) {
  unguarded( "restore_object", "/daemons/data/did_d.o" );
}

void create( void ) {
  did = ({ });
  restore_me();
}

void add_entry( string str ) {
  object *usr;
  int i;

  if( !file_exists( wiz_dir( this_user() ) ) ) {
    write( "Sorry, only true wizards may add to the did log.\n" );
    return;
  }
  str = capitalize( this_user()->query_name() ) + " " + str;
  did += ({ ({ time(), str }) });
  save_me();

  usr = USER_D->query_users();
  for( i = 0; i < sizeof( usr ); i++ ) {
    if( query_wizard( usr[i]->query_player()->query_name() ) > 0 && usr[i] != this_user() ) {
      usr[i]->query_player()->message( "** " + str );
    }
  }
  write( "Reported. Thank you!\n" );
}

int start_index( int after ) {
  int index;

  index = sizeof( did );

  while( index > 0 && did[index-1][0] > after )
    index--;

  return index;
}

string *get_entries(int after)
{
    int index;
    string *output;

    index = start_index(after);

    if ( index >= sizeof(did) )
      return nil;

    output = ({ "Change Log\n",
		"**********\n" });

    for ( ; index < sizeof(did); index++ ) {
      output += ({ ctime(did[index][0]) + ": " +did[index][1] + "\n" });
      output += ({ "" });
    }
    return output;
}
