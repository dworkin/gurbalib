void usage() {
  write("Usage: showemote [-h] [EMOTE]\n");
  write("Show the entry for emote EMOTE.  If EMOTE is missing, " +
    "list all emotes.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  string *rules;
  int i;
  string line;

  if (!str || str == "") {
     rules = EMOTE_D->query_emotes( );

     line = "";

     for( i = 0; i < sizeof( rules ); i++ ) {
        line += rules[i] + ", ";
     }
     write(line + "\n");
     write( " \nTotal: " + sizeof(rules) + "\n" );
     return;
  } 
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( EMOTE_D->is_emote( str ) ) {

    rules = EMOTE_D->query_rules( str );

    while( sizeof( rules ) > 0 ) {
      write( rules[0] + " : \"" + EMOTE_D->query_emote( str, rules[0] ) + 
         "\"\n" );
      rules -= ({ rules[0] });
    }
  } else {
    write( "No such emote. \n" );
  }
}
