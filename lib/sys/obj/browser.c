inherit "/sys/lib/menu";

#define TO this_object()

void browse( varargs string what );

static int show_file( string str ) {
  string stuff, path;

  path = this_player()->query_env( "cwd" );

  path = normalize_path( str, path );

  switch( file_exists( path ) ) {
    case 1 :
      if( valid_read( path ) ) {
        stuff = read_file( path );
        this_player()->more( explode( stuff, "\n" ) );
        return 2;
      } else {
        write( "Permission denied" );
        return 0;
      }
      break;
    case -1 :
      if( valid_read( path ) ) {
        browse(path);
        return 2;
      } else {
        write( "Permission denied" );
        return 0;
      }
    default :
      write( "File not found or no access" );
      return 0;
  }
}

static int menu_action_quit() {
  write( "Ok." );
  return 1;
}

void browse(varargs string what) {
  int k, i,sz;
  mixed *menu;
  mixed **files;
  string path;

  if( what && strlen( what ) && valid_read( what ) ) {
    path = normalize_path( what, "/" );
    this_player()->set_env( "cwd", path );
  } else {
    path = this_player()->query_env( "cwd" );
  }

  if( !path ) {
    path = "/";
    this_player()->set_env( "cwd", path );
  }

  files = get_dir( path + "/*" );
  menu = ({ });
  k = 1;

  for( i = 0, sz = sizeof( files[0] ); i < sz; i++ ) {
    menu += ({ ({ ""+(k++), files[0][i], ""+files[1][i], make_fcall( TO, "show_file", files[0][i] ) }) });
  }

  if( path != "/" ) {
    menu += ({ ({ "..", "..", nil, make_fcall( TO, "show_file", ".." ) }) });
  }

  menu += ({ ({ "q", "quit menu", nil, make_fcall( TO, "menu_action_quit" ) }) });

  do_menu( 
    "A test menu",
    menu
  );
}

static string get_display(string str) {
  return "Generated item "+str;
}

static int dotest( string str ) {
  switch( str ) {
    case "a" : write( "A: return to current menu" );
               return 0;
    case "b" : write( "B: exit menu" );
               return 1;
  }
}

