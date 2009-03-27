void main( string str ) {

  string error, name;
  object env;
  string filename;

  name = this_player()->query_name();

  filename = "/wiz/" + name + "/rooms/workroom";

  if( !file_exists( filename + ".c" ) ) {
    filename = "/wiz/" + name + "/workroom";

    if( file_exists( filename + ".c" ) ) {
      if( file_exists( "/wiz/" + name + "/rooms" ) == 0 ) {
        write("Please create a /wiz/"+name+"/rooms directory and "+
              "move your workroom into it.");
      } else {
        write("Please move your workroom into /wiz/"+name+"/rooms/");
      }
    }
  }

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
