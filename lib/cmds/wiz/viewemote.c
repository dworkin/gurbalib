void usage() {
  write("Usage: viewemote [-h] EMOTE\n");
  write("Look at available emotes to see if EMOTE is listed, if so display " +
    "what it does.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  string *rules;
  int i;

  if (!str || str == "") {
     usage();
     return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }


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
