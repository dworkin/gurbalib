void usage() {
  write("Usage: home [-h]\n");
  write("Transport you to your \"work room\".\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: goto, summon, where\n");
}

void main( string str ) {

  string error, name;
  object env;
  string filename;

  if (str && (str != "")) {
     usage();
     return;
  }

  name = this_player()->query_name();

  filename = WIZ_DIR + name + "/rooms/workroom";

  if( !file_exists( filename + ".c" ) ) {
    filename = WIZ_DIR + name + "/workroom";

    if( file_exists( filename + ".c" ) ) {
      if( file_exists( WIZ_DIR + name + "/rooms" ) == 0 ) {
        write("Please create a " + WIZ_DIR + name + "/rooms directory and "+
              "move your workroom into it.");
      } else {
        write("Please move your workroom into " + WIZ_DIR + name + "/rooms/");
      }
    }
  }

  if( !file_exists( filename + ".c" ) ) {
    write( "Make one first.\n" );
    return;
  }

  env = this_player()->query_environment();

  this_player()->simple_action( "$N $vgo home." );
  this_player()->move(filename);
  if( !error ) {
    this_player()->do_look( 0 );
  } else {
    env->tell_room( this_player(), 
       this_player()->query_Name() + " looks confused." );
    write( "You can't go home.\nError: " + error );    
  }
}
