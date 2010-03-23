void main(string str) {
  if(str == "") {
    write("Banish whom?\n");
    return;
  }

  if( str == "woodie" || str == "stubbs" || str == "fudge" ) {
    write("Banish "+str+"?!? You must be kidding...\n");
    return;
  }

  if( strstr( str, " " ) != -1 ) {
    write("Cannot include whitespace in banished names.");
    return;
  }

  if( BANISH_D->banish_name( str ) ) {
    this_player()->simple_action( "$N $vbanish "+str+".\n" );
  } else {
    write( "Failed." );
  }
}

