void main( string str ) {
  string *rules;
  int i;

  if( EMOTE_D->is_emote( str ) ) {

    rules = EMOTE_D->query_rules( str );

    while( sizeof( rules ) > 0 ) {
      write( rules[0] + " : \"" + EMOTE_D->query_emote( str, rules[0] ) + "\"\n" );
      rules -= ({ rules[0] });
    }
  } else {
    write( "No such emote. \n" );
  }
}
