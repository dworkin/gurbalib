void usage() {
  write("Usage: clone [-h] [FILENAME]\n");
  write("Bring a copy of the object FILENAME into existence.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: warmboot, rebuild, update\n");
}

void main( string str ) {
  string path;
  object ob;

  if( !str || str == "" ) {
    str = this_player()->query_env( "cwf" );
  } else if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( !str || str == "" ) {
    write( "Please specify a file to clone." );
    return;
  }

  path = this_player()->query_env( "cwd" );

  if( strlen(str) > 2 ) {
    if( str[strlen(str)-2] == '.' 
	&& str[strlen(str)-1] == 'c' )
      str = str[..strlen(str)-3];
  }

  path = normalize_path( str, path );

  if( !path || path == "" ) {
    write( "Access denied.\n" );
    return;
  }

  if( file_exists( path + ".c" ) ) {
    ob = clone_object( path );
    this_player()->set_env( "cwf", path );
    if( ob ) {
      ob->move( this_player()->query_environment() );
      ob->setup();
      this_player()->simple_action( "$N $vclap $p hands and " + article( ob->query_id() ) + " " + ob->query_id() + " appears.\n" );

      if( ob->is_gettable() ) {
	ob->move( this_player() );
      } else {
	ob->move( this_environment() );
      }
    }
  } else {
    write( "File not found.\n" );
  }
}
