void main( string str ) {
  if( !str || str == "" ) {
    write( "Useage: mkwizdir <name>\n" );
    return;
  }
  if( require_priv( "system" ) ) {
    SECURE_D->create_homedir( str );
  } else {
    write( "You need admin priveleges to make wizards.\n" );
  } 
}
