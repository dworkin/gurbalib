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
#include <trace.h>
#include <tlsvar.h>
#include <privileges.h>

/*
 * Used by object_type(), maps between shortnames for
 * some common object types and their absolute path
 */
#define SHORT_OBJECT_TYPE ([\
  "player"     :"/std/player",\
  "user"       :"/std/user",\
  "connection" :"/kernel/obj/net/connection",\
  "port"       :"/kernel/obj/net/port",\
  "compiler"   :"/kernel/daemon/compiler"\
])

int query_tls_size();
void set_tls_size(int size);
mixed get_tlvar(int index);
void set_tlvar(int index, mixed value);

int tls_size;

object compiler_d;
object error_d;

void message(string str) {
  send_message(ctime(time())[4 .. 18] + " ** " + str);
}

object compile_object( string path, varargs string code ) {
  object ob;
     
  set_tlvar(TLS_INCLUDES, ({ "/kernel/include/std.h" }) );
  set_tlvar(TLS_INHERITS, ({ }) );
  set_tlvar(TLS_COMPILING, path);

  if(code) {
    ob = ::compile_object( path, code );
  } else {
    ob = ::compile_object( path );
  }

  if(get_tlvar(TLS_COMPILING) != AUTO && get_tlvar(TLS_COMPILING) != DRIVER) {
    set_tlvar( TLS_INHERITS, ({ find_object( AUTO ) }) | get_tlvar( TLS_INHERITS ) );
  }

  set_tlvar(TLS_COMPILING, nil);

  if(compiler_d) {
    compiler_d->register_includes( ob, get_tlvar(TLS_INCLUDES) );
    compiler_d->register_inherits( ob, get_tlvar(TLS_INHERITS) );
  }

  return ob;
}

void register_compiler_d() {
  if(KERNEL()) {
    message("Registering compiler_d: "+object_name(previous_object())+"\n");
    compiler_d = previous_object();
  }
}

void register_error_d() {
  if(KERNEL()) {
    message("Registering error_d: "+object_name(previous_object())+"\n");
    error_d = previous_object();
  }
}

static void _initialize(mixed * tls) {

  message( status()[ST_VERSION] + " running " + LIB_NAME + " " + LIB_VERSION + ".\n");
  message( "Initializing...\n" );
  call_other( COMPILER_D, "???" );
  call_other( ERROR_D, "???" );
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
  call_out( "clean_up", 60 );
  call_out( "heart_beat", 2 );
  message( "Done.\n" );
}

static void initialize() {
  tls_size = DEFAULT_TLS_SIZE + 2; 
  _initialize(allocate(query_tls_size()));
}

static void _heart_beat( mixed * tls ) {
  EVENT_D->event( "heart_beat" );
  call_out( "heart_beat", 2 );
}

static void heart_beat() {
  _heart_beat(allocate(query_tls_size()));
}

static void _clean_up( mixed * tls ) {
  EVENT_D->event( "clean_up" );
  call_out( "clean_up", 60 );
}

static void clean_up() {
  _clean_up(allocate(query_tls_size()));
}

object clone_object( string path ) {
  object ob;

  if( ob = find_object( path ) )
    return ::clone_object( ob );
  else
    return ::clone_object( compile_object( path ) );
}

static void _restored(mixed * tls) {
  message( "DGD " + status()[ST_VERSION] + " running Gurba.\n" );
  call_other("/daemons/telnet_d","initialize");
  message( "State restored.\n" );
}

static void restored() {
  _restored(allocate(query_tls_size()));
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
  string * old_includes;
  object * old_inherits;
  string old_compiling;

  if( !(ob = find_object( program )) ) {

    old_includes = get_tlvar( TLS_INCLUDES );
    old_inherits = get_tlvar( TLS_INHERITS );
    old_compiling = get_tlvar( TLS_COMPILING );
    set_tlvar( TLS_INCLUDES, ({ "/kernel/includes/std.h" }) );
    set_tlvar( TLS_INHERITS, ({ }) );
    set_tlvar( TLS_COMPILING, program );

    ob = ::compile_object( program );

    if(  get_tlvar( TLS_COMPILING ) != AUTO ) {
      set_tlvar(TLS_INHERITS, ({ find_object(AUTO) }) | get_tlvar(TLS_INHERITS) );
    }

    if(compiler_d) {
      compiler_d->register_includes(ob, get_tlvar(TLS_INCLUDES));
      compiler_d->register_inherits(ob, get_tlvar(TLS_INHERITS));
    }

    set_tlvar(TLS_COMPILING, old_compiling);
    set_tlvar(TLS_INCLUDES,old_includes);
    set_tlvar(TLS_INHERITS,old_inherits);
  }

  if(ob) {
    set_tlvar(TLS_INHERITS, get_tlvar(TLS_INHERITS) | ({ ob }) );
  }

  return ob;
}

string include_file( string file, string path ) {
  string res;


  if(compiler_d)  {
    res = compiler_d->include_file(file, path);
  } else {
    if( path[0] != '/' ) {
      res = file + "/../" + path;
    } else {
      res = path;
    }
  } 

  if(read_file(res)) {
    set_tlvar(TLS_INCLUDES, get_tlvar(TLS_INCLUDES) | ({ res }) );
  }
  return res;
}

void recompile( object obj ) {
  if( obj ) destruct_object( obj );
}

object _telnet_connect(mixed * tls, int port) {

  object connection;

  connection = clone_object( "/std/user" );
  return( connection );
}

object telnet_connect(int port) {
  return _telnet_connect(allocate(query_tls_size()), port);
}

object _binary_connect(mixed * tls, int port) {
}

object binary_connect(int port) {
  _binary_connect(allocate(query_tls_size()), port);
}


void _interrupt(mixed * tls) {
  object *usrs;
  object p;
  int i;

  usrs = users();
  for( i=0; i < sizeof( usrs ); i++ ) {
    p = usrs[i]->query_player();
    if(p) p->do_quit("");
    else destruct_object(usrs[i]);
  }
  message( "Shutting down." );
  shutdown();
}

void interrupt() {
  _interrupt(allocate(query_tls_size()));
}

void compile_error( string file, int line, string err ) {

  object usr;
  object plr;
  string error;

  /* Error during compiling */

  if( error_d ) {
    error_d->compile_error( file, line, err );
    return;
  }

  error = file + ", " + (string) line + ": " + err + "\n";
  send_message( error );
  write_file("/logs/errors/compile", error);
  usr = this_user();
  if( usr ) {
    if( usr->query_player() ) {
      if( SECURE_D->query_wiz( usr->query_player()->query_name() ) == 1 ) {
   usr->query_player()->write( error );
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
void runtime_error( string error, int caught, int ticks ) {
  mixed **trace;
  string progname, objname, function, str;
  int i, sz, line, len;
  object player;

  if(error_d) {
    error_d->runtime_error( error, call_trace(), caught, ticks , -1 );
    return;
  }

  if( caught ) {
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
  if(error_d) {
    error_d->runtime_error(error,call_trace(), 0,t,a);
  } else {
    runtime_error(error,0,t);
  }
}

static string object_type(string from, string obtype) {
  if(SHORT_OBJECT_TYPE[obtype]) {
    return SHORT_OBJECT_TYPE[obtype];
  } else {
    return normalize_path(obtype,from);
  }
}

int compile_rlimits( string objname ) {
  if(sscanf(objname,"/kernel/%*s") == 1 || sscanf(objname,"/daemons/%*s") == 1 || sscanf(objname,"/std/%*s") == 1 ) {
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

/*
 * tls support
 *
 */

void set_tls_size(int s) {
  if(KERNEL()) {
    tls_size = s + 2;
  }
}

int query_tls_size() {
    return tls_size;
}

mixed * new_tls() {
  if(KERNEL()) {
    return allocate(tls_size);
  }
}

mixed get_tlvar(int i) {
  if(KERNEL()) {
    return call_trace()[1][TRACE_FIRSTARG][i + 2];
  }
}

void set_tlvar(int i, mixed v) {
  if(KERNEL()) {
    call_trace()[1][TRACE_FIRSTARG][i + 2] = v;
  }
}

static int _touch(mixed tls, object ob, string function) {
  object savep;
  object * clones;
  int i;

  message("touching "+object_name(ob)+ " due to a call to "+function+"\n");

  rlimits(MAX_DEPTH; MAX_TICKS) {
    ob->upgraded();
  }
}

int touch(object ob, string function) {
  return _touch(allocate(query_tls_size()),ob,function);
}

