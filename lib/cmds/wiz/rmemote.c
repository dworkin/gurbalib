void main( string str ) {

  if( str == "" ) {
    write( "Useage: rmemote <name>\n" );
    return;
  }

  if( EMOTE_D->is_emote(str) ) {
    EMOTE_D->remove_emote( str );
    write( "Emote removed.\n" );
  } else {
    write( "No such emote.\n" );
  }
}
