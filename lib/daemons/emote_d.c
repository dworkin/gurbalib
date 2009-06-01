mapping emotes;
string *adverbs;

static void save_me( void ) {
  unguarded( "save_object", "/daemons/data/emote_d.o" );
}

static void restore_me( void ) {
  unguarded( "restore_object", "/daemons/data/emote_d.o" );
}

void create( void ) {
  emotes = ([ ]);
  adverbs = ({ });
  restore_me();
}

void add_addverb( string str ) {
  adverbs -= ({ str });
  adverbs += ({ str });
  save_me();
}

void remove_addverb( string str ) {
  adverbs -= ({ str });
  save_me();
}

void add_emote( string name, string rule, string fmt ) {
  if( rule != "STR" && rule != "LIV" && rule != "OBJ" ) {
    rule = "";
  }

  if( !emotes[name] ) 
    emotes[name] = ([ ]);
  emotes[name][rule] = fmt;
  save_me();
}

int is_emote( string name ) {
  if( !emotes[name] )
    return( 0 );
  else
    return( 1 );
}

string *query_emotes( void ) {
  return( map_indices( emotes ) );
}

string query_emote( string name, string rule ) {
  return( emotes[name][rule] );
}

string *query_rules( string name ) {
  return( map_indices( emotes[name] ) );
}

void remove_emote( string name ) {
  emotes[name] = nil;
  save_me();
}
