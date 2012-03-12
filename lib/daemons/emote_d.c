mapping emotes;

static void save_me( void ) {
  unguarded( "save_object", "/daemons/data/emote_d.o" );
}

static void restore_me( void ) {
  unguarded( "restore_object", "/daemons/data/emote_d.o" );
}

void create( void ) {
  emotes = ([ ]);
  restore_me();
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

// XXX Change this so it returns an array of lines so we can more it.
// also work it into cmds.c with -e flag....
void show_emote(string str) {
   string *rules;
   int i;
   string line;

   if (!str || str == "") {
      rules = query_emotes( );

      line = "";

      for( i = 0; i < sizeof( rules ); i++ ) {
         line += rules[i] + ", ";
      }
      write(line + "\n");
      write( " \nTotal: " + sizeof(rules) + "\n" );

      return;
   }
   if( is_emote( str ) ) {

      rules = query_rules( str );

      while( sizeof( rules ) > 0 ) {
         write( rules[0] + " : \"" + query_emote( str, rules[0] ) +
            "\"\n" );
         rules -= ({ rules[0] });
      }
   } else {
      write( "No such emote. \n" );
   }
}

