void main( string str ) {
  string *emotes;
  int i;
  string line;

  emotes = EMOTE_D->query_emotes( );

  line = "";

  for( i = 0; i < sizeof( emotes ); i++ ) {
     line += emotes[i] + ", ";
  }
  write(line + "\n");
  write( " \nTotal: " + sizeof(emotes) + "\n" );
}
