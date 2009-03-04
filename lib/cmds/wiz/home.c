void main( string str ) {

  string error;
  object env;
  string filename;

  filename = "/wiz/" + this_player()->query_name() + "/workroom";

  if( !file_exists( filename + ".c" ) ) {
    write( "Make one first.\n" );
    return;
  }

  env = this_player()->query_environment();

  error = catch( this_player()->move( filename ) );

  if( !error ) {
    this_player()->simple_action( "$N $vgo home." );
    this_player()->do_look( 0 );
  } else {
    env->tell_room( this_player(), capitalize( this_player()->query_name() ) + " looks confused." );
    write( "You can't go home.\nError: " + error );    
  }
}
