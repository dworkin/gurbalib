void main( string str ) {
  if( !str || str == "" ) {
    write( "Useage: mkwiz <name>\n" );
    return;
  }
  if( require_priv( "system" ) ) {
    SECURE_D->make_wizard( str );
  } else {
    write( "You need admin priveleges to make wizards.\n" );
  } 
}
