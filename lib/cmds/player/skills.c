void main( string str ) {
  string *skills;
  int i;
  string line;

  skills = this_player()->query_skills();

  if( sizeof( skills ) == 0 ) {
    write( "You are unskilled." );
    return;
  }

  for( i = 0; i < sizeof( skills ); i++ ) {
    line = skills[i] + "                                     ";
    line = line[0..20] + ": " + this_player()->query_skill( skills[i] );
    write( line );
  }
}