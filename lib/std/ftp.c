int timeout_handle;
string name;
string password;
private mapping cmds;
int connected;
string cwd;
int priv;
int binary;

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

void FTPLOG( string str ) {
  write_file( "/logs/errors/ftpd", ctime( time() ) + " : " + str );
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
  password = crypt( arg, "gurba" );
  player = clone_object( "/std/player" );
  player->set_name( name );
  player->restore_me();
  if( password != player->query_password() ) {
    send_message( "530 Login incorrect.\n" );
    return;
  }
  destruct_object( player );
  send_message( "230 User " + name + " logged in.\n" );
  priv = SECURE_D->query_priv( name );
  FTPLOG( name + " logged in.\n" );
  connected = 1;
  cwd = "/";
}

void FTP_CMD_retr( string arg ) {

}

void FTP_CMD_stor( string arg ) {

}

void FTP_CMD_nlst( string arg ) {

}

void FTP_CMD_pwd( string arg ) {
  send_message( "257 \"" + cwd + "\" is current directory.\n" ); 
}

void FTP_CMD_cdup( string arg ) {

}

void FTP_CMD_cwd( string arg ) {

}

void FTP_CMD_quit( string arg ) {
  send_message( "221 Goodbye.\n" );
  FTPLOG( name + " quit.\n" );
  destruct_object( this_object() );
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

}

void FTP_CMD_port( string arg ) {
  string ip;
  string *parts;
  int    port;
  
  parts = explode( arg, "," );
  if( sizeof( parts ) != 6 ) {
    send_message("550 Failed command.\n");
    return;
  }
  ip = implode( parts[0..3], "." );

  /* Make a 16 bit port # out of two 8 bit values. */
  port = (str2val(parts[4]) << 8) + str2val(parts[5]);
  switch(info->binary) {
  case 0:
    break;
  case 1:
    break;
  default:
    return;
  }
  send_message("200 PORT command successful.\n");
  return;
}

void FTP_CMD_noop( string arg ) {
  send_message("221 NOOP command successful.\n");
}

void FTP_CMD_dele( string arg ) {

}

void FTP_CMD_syst( string arg ) {
  send_message( "215 UNIX Mud name: Gurba\n" );
}

void FTP_write( void ) {
  send_message( "226 Transfer complete.\n" );
}

void receive_message( string message ) {
  string cmd, arg;
  string func;

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

  FTPLOG( "Got: " + message + "\n" );

  if( connected == 0 ) {
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
  if(catch(call_other(this_object(), func, arg))) {
    FTPLOG(name + " caused a FAILURE with command '" + message + "'.\n" );
    send_message("550 Unknown failure.  Please report what you were doing to the mud admin.\n");
  }
  return;
}


void login_timeout( void ) {
  send_message( "220 Timed out.\n" );
  destruct_object( this_object() );
}
