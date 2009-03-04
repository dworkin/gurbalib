void main( string str ) {
  if( str == "" ) {
    write( "Useage: addadverb <adverb>\n" );
    return;
  }

  EMOTE_D->add_adverb( lowercase(str) );
  write( "Addverb added.\n" );
}