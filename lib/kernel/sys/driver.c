/* $Id: driver.c,v 1.4 1998/02/22 13:43:51 esimonse Exp $ */

/* $Log: driver.c,v $
 * Revision 1.4  1998/02/22 13:43:51  esimonse
 * Added support for editing
 *
 * Revision 1.3  1998/01/29 16:11:58  esimonse
 * Added Id and Log.
 * */

#include <status.h>
#include <ports.h>

/*
 * Used by object_type(), maps between shortnames for
 * some common object types and their absolute path
 */
#define SHORT_OBJECT_TYPE ([\
  "player"     :"/std/player",\
  "user"       :"/std/user",\
  "connection" :"/kernel/obj/net/connection"\
])

private object load( string path ) {
  object ob;

  ob = find_object( path );
  return( ob ) ? ob : compile_object( path );
}

void message(string str) {
  send_message(ctime(time())[4 .. 18] + " ** " + str);
}

static initialize() {

  message( status()[ST_VERSION] + " running " + LIB_NAME + " " + LIB_VERSION + ".\n");
  message( "Initializing...\n" );
  message( "Preloading...\n" );
  compile_object( STARTING_ROOM );

  message( "Setting up events\n" );
  EVENT_D->add_event( "clean_up" );
  EVENT_D->add_event( "player_login" );
  EVENT_D->add_event( "player_logout" );
  EVENT_D->add_event( "heart_beat" );
  EVENT_D->add_event( "new_player" );

  message( "Setting up daemons\n" );
  call_other( CHANNEL_D, "???" );
  call_other( TIME_D, "???" );
#ifdef SYS_NETWORKING
  call_other( TELNET_D, "???" );
  call_other( FTP_D, "???" );
  call_other( IMUD_D, "???" ); 
#endif
  call_other( OBJECT_D, "???" );
  call_other( RACE_D, "???" );
  call_other( SKILL_D, "???" );
  call_other( MONEY_D, "???" );
  call_other( BANISH_D, "???" );
  call_other( SITEBAN_D, "???" );
  call_other( GUILD_D, "???" );
  call_other( LANGUAGE_D, "???" );
  call_other( PARSE_D, "???" );

  message( "Setting up call outs\n" );
  call_out( "swapswap", 1800 );
  call_out( "clean_up", 60 );
  call_out( "heart_beat", 2 );
  message( "Done.\n" );
}

static void heart_beat( void ) {
  EVENT_D->event( "heart_beat" );
  call_out( "heart_beat", 2 );
}

static void clean_up( void ) {
  EVENT_D->event( "clean_up" );
  call_out( "clean_up", 60 );
}

static void swapswap() {
  swapout();
  call_out( "swapswap", 1800 );
}

object clone_object( string path ) {
  object ob;

  if( ob = find_object( path ) )
    return ::clone_object( ob );
  else
    return ::clone_object( compile_object( path ) );
}

static restored() {
  message( "DGD " + status()[ST_VERSION] + " running Gurba.\n" );
  call_other("/daemons/telnet_d","initialize");
  message( "State restored.\n" );
}

/*
 * NAME: normalize_path()
 * DESCRIPTION:   reduce a path to its minimal absolute form
 */
string normalize_path(string file, string dir)
{
  string *path;
  int i, j, sz;

  if (strlen(file) == 0) {
    file = dir;
  }
  switch (file[0]) {
  case '~':
    /* ~path */
    if(strlen(file) == 1 || file[1] == '/') {
      file = "/wiz/" + this_user()->query_name() + file[1 ..];
    } else {
      file = "/wiz/" + file[1 ..];
    }
    /* fall through */
  case '/':
    /* absolute path */

    path = explode(file, "/");

    if( (path[0] == "data" || path[0] == "kernel") && !SECURE_D->query_admin( this_user()->query_name() ) )
      return("");

    if (sscanf(file, "%*s//") == 0 && sscanf(file, "%*s/.") == 0) {
      return file;   /* no changes */
    }
    break;

  default:
    /* relative path */
    if (sscanf(file, "%*s//") == 0 && sscanf(file, "%*s/.") == 0 &&
   sscanf(dir, "%*s/..") == 0) {
      /*
       * simple relative path
       */

      if( dir[strlen(dir)-1] == '/' )
   path = explode( dir + file, "/" );
      else
   path = explode( dir + "/" + file, "/" );

      if( (path[0] == "data" || path[0] == "kernel") && !SECURE_D->query_admin( this_user()->query_name() ) )
   return("");


      if( dir[strlen(dir)-1] == '/' )
   return dir + file;
      else
   return dir + "/" + file;
    }
    /* fall through */
  case '.':
    /*
     * complex relative path
     */
    path = explode(dir + "/" + file, "/");
    break;
  }

  for (i = 0, j = -1, sz = sizeof(path); i < sz; i++) {
    switch (path[i]) {
    case "..":
      if (j >= 0) {
   --j;
      }
      /* fall through */
    case "":
    case ".":
      continue;
    }
    path[++j] = path[i];
  }

  if( (path[0] == "data" || path[0] == "kernel") && !SECURE_D->query_admin( this_user()->query_name() ) ) {
    return "";
  }

  return "/" + implode(path[.. j], "/");
}

string path_read( string path ) {

  string file;

  file = normalize_path( path, this_user()->query_player()->query_env("cwd") );
  return( file );
}

string path_write( string path ) {
  string file;

  file = normalize_path( path, this_user()->query_player()->query_env("cwd") );
  return( file );
}

object call_object( string name ) {
  object ob;

  if( ob = find_object(name) )
    return ob;
  ob = compile_object(name);
  return ob;
}

object inherit_program( string file, string program, int priv ) {
  object ob;

  if( ob = find_object( program ) )
    return ob;
  else
    return compile_object( program );
}

string include_file( string file, string path ) {
  if( path[0] != '/' ) {
    return file + "/../" + path;
  } else {
    return path;
  }
}

void recompile( object obj ) {
  message( "recompile( obj );\n" );
}

object telnet_connect(int port) {

  object connection;
  
  
#ifdef SYS_NETWORKING
  connection = find_object(TELNET_D);
  return( connection );
#else
  connection = clone_object( "/std/user" );
  return( connection );
#endif
  }

#ifdef SYS_NETWORKING
object binary_connect(int port) {
  object connection;
	
	message(FTP_PORT);
  /*switch(port) {
    case FTP_PORT :
      connection = find_object(FTP_D);
      break;
    }*/
  }
#endif

void interrupt() {
  object *usrs;
  object p;
  int i;

  for( i=0; i < sizeof( usrs ); i++ ) {
    p = usrs[i]->query_player();
    if(p) p->do_quit();
    else destruct_object(p);
  }
  message( "Shutting down." );
  shutdown();
}

void compile_error( string file, int line, string err ) {

  object usr;
  object plr;
  string error;

  /* Error during compiling */

  error = file + ", " + (string) line + ": " + err + "\n";
  send_message( error );
  write_file("/logs/errors/compile", error);
  usr = this_user();
  if( usr ) {
    if( usr->query_player() ) {
      if( SECURE_D->query_wiz( usr->query_player()->query_name() ) == 1 ) {
   usr->query_player()->write( err );
      } else {
   usr->query_player()->write( "You have encountered a rift in reality. Please report it to the admins.\n" );
      }
    }
  }
}

/*
 * NAME:	runtime_error()
 * DESCRIPTION:	log a runtime error
 */
void runtime_error( string error, int cought, int ticks ) {
  mixed **trace;
  string progname, objname, function, str;
  int i, sz, line, len;
  object player;

  if( cought ) {
    return;
  }

  trace = call_trace();

  if( (sz=sizeof(trace) - 1) != 0 ) {
    for( i=0; i<sz; i++ ) {
      progname = trace[i][1];
      function = trace[i][2];
      objname = trace[i][0];
      line = trace[i][3];
      if( line == 0 ) {
	str = "    ";
      } else {
	str = "    " + line;
	str = str[strlen( str ) - 4 ..];
      }
      str += " " + function + " ";
      len = strlen( function );
      if( len < 17 ) {
	str += "                 "[len ..];
      }
      str += progname;
      if( progname != objname ) {
	len = strlen(progname);
	if( len < strlen(objname) && progname == objname[.. len - 1]) {
	  str += " (" + objname[len ..] + ")";
	} else {
	  str += " (" + objname + ")";
	}
      }
      send_message( str + "\n" );
    if(i == 0) {
      send_message(error + "\nObject: " + objname + ", program: " + progname + ", line " + line + "\n" );
      if( this_user() ) {
	player = this_user()->query_player();
	if( player ) {
	    player->write( error + "\nObject: " + objname + ", program: " + progname + ", line " + line + "\n" );
	  }
	}
      }
    }
  }
}

static void atomic_error(string error, int a, int t) {
    error = "(atom: "+a+", "+t+" ticks remaining) "+error;
    runtime_error(error,0,t);
}

static string object_type(string from, string obtype) {
  if(SHORT_OBJECT_TYPE[obtype]) {
    return SHORT_OBJECT_TYPE[obtype];
  } else {
    return normalize_path(obtype,from);
  }
}

int compile_rlimits( string objname ) {
  if(sscanf(objname,"/kernel/%*s") == 1 || sscanf(objname,"/daemons/%*s") == 1) {
    message( "compile rlimits permitted for " + objname + "\n" );
    return 1;
  } else {
    message( "compile rlimits denied for " + objname + "\n" );
  }
}

int runtime_rlimits( object obj, int stack, int ticks ) {
  string * objname;
  objname = explode(object_name(obj),"/");
  switch(objname[0]) {
    case "kernel"  :
    case "daemons" : return 1;
                     break;
    default        : message("runtime rlimits denied for "+object_name(obj)+"\n");
                     break;
  }
}

void remove_program( string ob, int t, int issue ) {
  message("Program "+ob + ", issue:"+issue+" ("+ctime(t)+") is no longer referenced\n" );
}
