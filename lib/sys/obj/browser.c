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

private string format_file_info( string f, int size, int ts ) {
  string result;
  string tmp;

  result = "";

  switch( size ) {
    case -2 :
      tmp = "DIR       ";
      break;
    default :
      tmp = "             " + size;
      tmp = tmp[ strlen( tmp ) - 10 .. ];
      break;
  }

  result += tmp + " ";

  tmp = owner_file( normalize_path( f, "/" ) ) + "                ";
  tmp = tmp[0..15];

  result += tmp + " ";
  result += ctime( ts );
  return result;
}
  
void browse(varargs string what) {
  int k, i,sz;
  mixed *menu;
  mixed **files;
  string path;

  if( what && strlen( what ) && valid_read( what ) ) {
    switch( file_exists( what ) ) {
      case 1 :
        show_file( what );
        return;
        break;
      case -1 :
        path = normalize_path( what, "/" );
        this_player()->set_env( "cwd", path );
        break;
      default :
        write( "No such file or directory or no access." );
        return;
        break;
    }
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
    menu += ({ ({ ""+(k++), files[0][i], format_file_info( path + "/" + files[0][i], files[1][i], files[2][i] ), make_fcall( TO, "show_file", files[0][i] ) }) });
  }

  if( path != "/" ) {
    menu += ({ ({ "..", "<previous directory>", nil, make_fcall( TO, "show_file", ".." ) }) });
  }

  menu += ({ ({ "q", "quit menu", nil, make_fcall( TO, "menu_action_quit" ) }) });

  do_menu( 
    "Browsing: "+path ,
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

