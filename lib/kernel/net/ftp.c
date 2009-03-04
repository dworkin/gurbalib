#define CHUNK_SIZE 8192

int timeout_handle;
string name;
string password;
private mapping cmds;
int connected;
string cwd;
int priv;
int binary;
object connection;
string file_name;
int filesize;
string chunk;
string store_file_name;
int where;

void FTP_connection_wait( void );
void FTP_CMD_list( string str );


void open( void ) {
  send_message( "220-GurbaLib FTP daemon v0.01 ready.\n" );
  send_message( "220 Use your mud name as login.\n" );
  cmds = ([
	   "user" : "FTP_CMD_user",
	   "pass" : "FTP_CMD_pass",
	   "retr" : "FTP_CMD_retr",
	   "stor" : "FTP_CMD_stor",
	   "nlst" : "FTP_CMD_nlst",
	   "list" : "FTP_CMD_list",
	   "pwd"  : "FTP_CMD_pwd",
	   "cdup" : "FTP_CMD_cdup",
	   "cwd"  : "FTP_CMD_cwd",
	   "quit" : "FTP_CMD_quit",
	   "type" : "FTP_CMD_type",
	   "mkd"  : "FTP_CMD_mkd",
	   "port" : "FTP_CMD_port",
	   "noop" : "FTP_CMD_noop",
	   "dele" : "FTP_CMD_dele",
	   "syst" : "FTP_CMD_syst",
	   ]);
  connected = 0;
  name = "";
  timeout_handle = call_out( "login_timeout", 120 );
}

void close( void ) {
  if( connection ) {
    destruct_object( connection );
  }
  destruct_object( this_object() );
}

string query_name( void ) {
  return( name );
}

void FTPLOG( string str ) {
  write_file( "/logs/ftpd", ctime( time() ) + " : " + str );
}

void FTP_CMD_user( string arg ) {
  arg = lowercase(arg);
  if(connected) {
      send_message("530 User " + arg + " access denied.\n");
      return;
  }
  name = arg;

  if(name == "ftp" || name == "anonymous" ) {
    send_message("331 Guest login ok, send your complete e-mail address as password.\n");
    return;
  }

  send_message("331 Password required for " + arg + ".\n");
  return;
}

void FTP_CMD_pass( string arg ) {

  object player;

  if( name == "" ) {
    send_message( "530 Login with USER first.\n" );
    return;
  }

  if( name == "ftp" || name == "anonymous" ) {
    send_message("230 guest login ok, access restrictions apply.\n");
    connected = 1;
    priv = 0;
    cwd = "/pub";
    FTPLOG("Anomymous login (" + arg + ")\n" );
    return;
   }
  password = crypt( arg, "fudge" );
  player = clone_object( "/std/player" );
  player->set_name( name );
  player->restore_me();
  if( password != player->query_password() ) {
    send_message( "530 Login incorrect.\n" );
    destruct_object( this_object() );
    return;
  }
  send_message( "230 User " + name + " logged in.\n" );
  FTPLOG( name + " logged in.\n" );
  connected = 1;
  cwd = "/";
  priv = SECURE_D->query_priv( name );
}

void FTP_CMD_retr( string str ) {

  if( !str ) {
    send_message( "550 No file selected.\n" );
    destruct_object( connection );
    return;
  }
  
  str = normalize_path( str, cwd );
  if( str == "" ) {
    send_message( "550 " + str + ": Permission denied.\n" );
    destruct_object( connection );
    return;
  }

  
  if( file_exists( str ) < 0 ) {
    send_message( "550 " + str + ": No such file.\n" );
    destruct_object( connection );
    return;
  }

  chunk = read_file( str, 0, CHUNK_SIZE );

  filesize = file_size( str );
  file_name = str;

  if( !binary ) {
    where = strlen( chunk );
    chunk = implode( explode( chunk, "\n" ), "\r\n" );
    send_message("150 Opening ASCII mode data connection for " + str + " (" + filesize + " bytes).\n" );
  } else {
    where = strlen( chunk );
    send_message("150 Opening binary mode data connection for " + str + " (" + filesize + " bytes).\n" );
  }

  if( filesize < CHUNK_SIZE ) {
    connection->set_callback( "FTP_write" );
    connection->send_data( chunk );
  } else {
    connection->set_callback( "FTP_retr" );
    connection->send_data( chunk );
  }

  FTPLOG( name + " GOT " + str + ".\n" );
}

void FTP_CMD_stor( string arg ) {

  string path;
  string *dirs;
  string dir;

  if( !priv ) {
    send_message( "550 Permission denied.\n" );
    return;
  }

  path = normalize_path( arg, cwd );
  if( path == "" ) {
    send_message( "550 Permission denied.\n" );
    return;
  }
  
  store_file_name = path;

  dirs = explode( path, "/" );
  dir = implode( dirs[..sizeof(dirs)-2], "/" );
  if( strlen( dir ) > 2 )
    dir = dir[..strlen(dir)-1];
  if( file_exists( dir ) != -1 ) {
    send_message( "553 No such directory to STOR into. (" + dir + ")\n" );
    return;
  }
  if( file_exists( store_file_name ) )
    remove_file( store_file_name );

  connection->set_read_callback( "FTP_stor" );

  if( !binary ) {
    send_message( "150 Opening ASCII mode data connection for "+arg+".\n" );
  } else {
    send_message( "150 Opening binary mode data connection for "+arg+".\n" );
  }
  where = 0;
  FTPLOG( name + " PUT " + store_file_name + ".\n" );
}

void FTP_CMD_nlst( string str ) {
  mixed *files, *objects;
  string *names, timestr, size, dirlist;
  int *sizes, *times, long, ancient, i, j, sz, max, len, rows, time;


  if( str == "-l" ) {
    FTP_CMD_list( "./" );
    return;
  }

  if( !str ) {
    str = ".";
  } else if (sscanf(str, "-%s", str) != 0) {
    long = 1;
    if (str == "l") {
      str = ".";
    } else if (sscanf(str, "l %s", str) == 0) {
      return;
    }
  }
  
  str = normalize_path( str, cwd );
  if( str == "" ) {
    send_message( "550 " + str + ": Permission denied.\n" );
    destruct_object( connection );
    return;
  }

  
  files = get_dir( str );

  if( !files ) {
    send_message( "550 " + str + ": No such file or directory.\n" );
    destruct_object( connection );
    return;
  }
  
  files = get_dir(str + "/*");
  if (!files) {
    send_message( "550 " + str + ": Permission denied.\n");
    destruct_object( connection );
    return;
  }
  
  names = files[0];
  sz = sizeof(names);
  if (!sz) {
    send_message( "550 No files found.\n" );
    destruct_object( connection );
    return;
  }
  sizes = files[1];
  times = files[2];

  dirlist = "";

  for( i = 0; i < sizeof( names ); i++ ) {
    dirlist += names[i] + "\r\n";
  }
  send_message("150 Opening ASCII mode data connection for file list.\n");
  connection->set_callback( "FTP_write" );
  connection->send_data( dirlist );
}

string FTP_myctime( int nTime ) {

  string zDate;
  string zWeekday, zMon, zTime, zYear;
  string zThis_year;
  string zDay;
  int nDay;

  zDate = ctime( nTime );
  sscanf( zDate, "%s %s %d %s %s", zWeekday, zMon, nDay, zTime, zYear );
  zThis_year = ctime( time() )[20..];

  zDay = "";
  zDay += nDay;
  if( strlen( zDay ) == 1 ) {
    zDay = " " + zDay;
  }

  if( zYear == zThis_year ) {

    return ( zMon + " " + zDay + " " + zTime[0..4] );
  } else {
    return ( zMon + " " + zDay + "  " + zYear );
  }
}

void FTP_CMD_list( string str ) {
  mixed *files, *objects;
  string *names, timestr, size, dirlist;
  int *sizes, *times, long, ancient, i, j, sz, max, len, rows, time;

  if( !str ) {
    str = ".";
  } else if (sscanf(str, "-%s", str) != 0) {
    long = 1;
    if (str == "l") {
      str = ".";
    } else if (sscanf(str, "l %s", str) == 0) {
      return;
    }
  }
  
  str = normalize_path( str, cwd );
  if( str == "" ) {
    send_message( "550 " + str + ": Permission denied.\n" );
    destruct_object( connection );
    return;
  }

  
  files = get_dir( str );

  if( !files ) {
    send_message( "550 " + str + ": No such file or directory.\n" );
    destruct_object( connection );
    return;
  }
  
  files = get_dir(str + "/*");
  if (!files) {
    send_message( "550 " + str + ": Permission denied.\n");
    destruct_object( connection );
    return;
  }
  
  names = files[0];
  sz = sizeof(names);
  if (!sz) {
    send_message( "550 No files found.\n" );
    destruct_object( connection );
    return;
  }
  sizes = files[1];
  times = files[2];

  dirlist = "";

  for( i = 0; i < sizeof( names ); i++ ) {
    if( sizes[i] < 0 ) {
      /* We're dealing with a directory */
      dirlist += "drwxr-xr-x   1 gurba    gurba        1024 " + FTP_myctime( times[i]) + " " + names[i] + "\r\n";
    } else {
      /* We're dealing with a file */
      dirlist += "-rw-r--r--   1 gurba    gurba ";
      size = "                    " + sizes[i];
      size = size[strlen(size)-11.. ];
      dirlist += size + " " + FTP_myctime( times[i]) + " " + names[i] + "\r\n";
    }

  }
  send_message("150 Opening ASCII mode data connection for /bin/ls.\n");
  connection->set_callback( "FTP_write" );
  connection->send_data( dirlist );
}

void FTP_connection_wait( void ) {
  if( !connection->is_connected() ) {
    call_out( "FTP_connection_wait", 1 );
    return;
  }
  send_message( "200 PORT command successful.\n" );
}

void FTP_CMD_pwd( string arg ) {
  send_message( "257 \"" + cwd + "\" is current directory.\n" ); 
}

void FTP_CMD_cwd( string arg ) {

  arg = normalize_path( arg, cwd );

  if( arg == "" ) {
    send_message( "550 " + arg + ": Permission denied.\n" );
    return;
  }

  if( strlen(arg) > 1 && arg[strlen(arg)-1] == '/' ) {
    arg = arg[..strlen(arg)-2];
  }
    
  if( file_exists( arg ) != -1 ) {
    send_message( "550 " + arg + ": No such file or directory.\n" );
    return;
  }
  cwd = arg;
  send_message("250 CWD command successful.\n");
}

void FTP_CMD_cdup( string arg ) {
  FTP_CMD_cwd( ".." );
}

void FTP_CMD_quit( string arg ) {
  send_message( "221 Goodbye.\n" );
  FTPLOG( name + " quit.\n" );
}

void FTP_CMD_type( string arg ) {
  switch(arg) {
  case "a":
  case "A":
    binary = 0;
    send_message("200 Type set to A.\n");
    return;
  case "i":
  case "I":
    binary = 1;
    send_message("200 Type set to I.\n");
    return;
  default:
    send_message("550 Unknown file type.\n");
    return;
  }
}

void FTP_CMD_mkd( string arg ) {
  string file;

  file = normalize_path( arg, cwd );
  if( file == "" || !priv) {
    send_message( "550 Permission denied.\n" );
    return;
  }

  if( !file_exists( file ) ) {
    if( !make_dir( file ) ) {
      send_message( "550 Unable to create directory.\n" );
      return;
    } else {
      send_message( "257 MKD command successful.\n" );
      return;
    }
  } else {
    send_message( "550 File or dir already exists.\n" );
  }
}

void FTP_CMD_port( string arg ) {

  string *tmp;
  string ip;
  int     port;

  tmp = explode( arg, "," );

  if( sizeof( tmp ) != 6 ) {
    send_message( "500 PORT " + arg + " not understood.\n" );
    return;
  }

  ip = implode( tmp[0..3], "." );
  port = ( str2val( tmp[4] ) << 8 ) + ( str2val( tmp[5] ) );

  if( connection ) {
    destruct_object( connection );
  }

  connection = clone_object( "/kernel/net/ftp_conn" );
  connection->start_connection( ip, port, binary );
  FTP_connection_wait();
}

void FTP_CMD_noop( string arg ) {

}

void FTP_CMD_dele( string arg ) {
  string file;
  file = normalize_path( arg, cwd );
  if( file == "" || !priv) {
    send_message( "550 " + arg + ": Permission denied.\n" );
    return;
  }

  if( file_exists( file ) == -1 ) {
    if( !remove_dir( file ) ) {
      send_message( "550 " + arg + ": Not empty.\n" );
    } else {
      send_message( "250 DELE command successful.\n" );
    }
  } else if( file_exists( file ) != 0 ) {
    if( !remove_file( file ) ) {
      send_message( "550 " + arg + ": Unable to DELE.\n" );
    } else {
      send_message( "250 DELE command successful.\n" );
    }
  } else {
    send_message( "550 " + arg + ": Not found.\n" );
  }
}

void FTP_CMD_syst( string arg ) {
  send_message( "215 UNIX Mud name: Gurba\n" );
}

void FTP_write( void ) {
  send_message( "226 Transfer complete.\n" );
  destruct_object( connection );
}


void FTP_retr( void ) {

  string *converted;

  if( where < filesize ) {
    chunk = read_file( file_name, where, CHUNK_SIZE );
  }


  if( !binary && chunk != "" ) {
    if( chunk[strlen(chunk)-1] == '\n' )
      chunk += " ";
    if( chunk[0] == '\n' )
      chunk = " " + chunk;
    converted = explode( chunk, "\n" );
    chunk = implode( converted, "\r\n" );
  }

  if( (where + CHUNK_SIZE) > filesize ) {
    connection->set_callback( "FTP_write" );
  } 
  connection->send_data( chunk );
  where += CHUNK_SIZE;
}
 
void FTP_stor( string str ) {
  string *lines;

  if( !binary ) {
    lines = explode( str, "\r" );
    str = implode( lines, "" );
  }

  write_file( store_file_name, str );
}


void receive_message( string message ) {
  string cmd, arg;
  string func;

  /*  FTPLOG( "Got: \"" + message + "\"\n" ); */

  if( message != "" && strlen(message) >= 2 ) {
    if( message[strlen(message)-1] == '\n' ) {
      message = message[..strlen(message)-2];
    }
  }

  if( message != "" && strlen(message) >= 2 ) {
    if( message[strlen(message)-1] == '\r' ) {
      message = message[..strlen(message)-2];
    }
  }

  arg = "";
  if( sscanf( message, "%s %s", cmd, arg ) != 2 ) {
    cmd = message;
  }

  cmd = lowercase( cmd );

  if( !connected ) {
    /* Only allow these commands if not connected */
    switch( cmd ) {
    case "user" : 
      FTP_CMD_user( arg );
      return;
    case "pass":
      FTP_CMD_pass( arg );
      return;
    case "quit":
      FTP_CMD_quit( arg );
      return;
    case "noop":
      FTP_CMD_noop( arg );
      return;
    default:
      send_message("503 Log in with USER first.\n");
      return;
    }
  }
  func = cmds[cmd];
  if (!func)
    {
      /* Log command so we know what clients are trying to use */
      send_message( "502 Unknown command " + cmd + "\n" );
      return;
    }

  if((call_other(this_object(), func, arg))) {
    FTPLOG(name + " caused a FAILURE with command '" + message + "'.\n" );
    send_message("550 Unknown failure.  Please report what you were doing to the mud admin.\n");
  }
  return;
}


void login_timeout( void ) {
  if( !connected ) {
    send_message( "220 Timed out.\n" );
    destruct_object( this_object() );
  }
}

 