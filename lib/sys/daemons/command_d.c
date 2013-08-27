/*
 * Gurbalib command daemon
 *
 * by Aidil@Way of the Force
 *
 */

#include <privileges.h>

#define DATA_FILE "/sys/daemons/data/command_d.o"
#define secure() require_priv("system")

#define DEBUG_COMMAND_D

mapping cmdpriv;
static mapping commands;

void rehash();

static void DEBUG( string str ) {
  mixed verbose;
  if(this_player()) {
    verbose = this_player()->query_env("debug_commands");
    if(stringp(verbose) && (verbose == "on" || verbose == "1")) {
      verbose = 1;
    } else if(!intp(verbose)) {
      verbose = 0;
    }
    if(verbose) write(str);
  }
#ifdef DEBUG
  console_msg( str );
#endif
}

static int restore_me() {
  return unguarded( "restore_object", DATA_FILE );
}

static void save_me() {
  unguarded( "save_object", DATA_FILE );
}

static void create() {
  int i, sz;

  restore_me();

  if( !cmdpriv ) {
    cmdpriv = ([
      "/sys/cmds/admin"     : "system",
      "/sys/cmds/wiz"       : "wizard",
      "/cmds/player"        : "*",
    ]);
  }

  save_me();
  rehash();
}

static int access_check( string path ) {
  return ( cmdpriv[path] && ( ( cmdpriv[path] == "*" ) || require_priv( cmdpriv[path] ) ) );
}

static string file_to_cmdname( string file ) {
  string r;

  sscanf( file, "%s.c", r );
  DEBUG( "Adding " + file + " : " + dump_value( r ) + "\n" );
  return r;
}

void rehash() {
  int i,sz;
  string * syspath;
  string * cmds;

  if(!secure()) {
    error("Permission denied.");
  }
  syspath = map_indices( cmdpriv );
  commands = ([ ]);

  console_msg( "Rehashing command paths\n" );
  for( i = 0, sz = sizeof( syspath ); i < sz; i++ ) {
    cmds = get_dir( syspath[i] + "*.c" )[0];
    cmds = map_array( cmds, "file_to_cmdname", this_object() );
    commands[syspath[i]] = cmds;
    console_msg( syspath[i] + "		: " + sizeof( cmds ) + "\n" );
  }
  DEBUG( dump_value( commands ) + "\n" );
  console_msg( "Done.\n" );
}

int exec_command( string cmd, string arg, string *syspath ) {
  object cmd_ob;
  int i, sz;

  if(!previous_object()<-"/sys/lib/modules/m_cmds") error("Permission denied.");

  DEBUG( "exec_command: " + ( cmd ? cmd:"<NIL>" ) + " " + dump_value( syspath ) + "\n");
  if(!cmd || cmd == "") return -1;

  for( i = 0, sz = sizeof( syspath ); ( i < sz ) && !cmd_ob; i++ ) {
    DEBUG( "Locating " + cmd + " in " + syspath[i] + ": " );
    if( commands[syspath[i]] && sizeof( commands[syspath[i]] & ({ cmd }) ) ) {
      DEBUG( "found\n" );
      if( access_check( syspath[i] ) ) {
        cmd_ob = find_object( syspath[i] + cmd );
        if( !cmd_ob ) {
          cmd_ob = compile_object( syspath[i] + cmd );
        }
      } else {
        DEBUG( "but no access\n" );
      }
    } else {
      DEBUG( "not found\n" );
    }
  }

  if( cmd_ob && cmd_ob<-M_COMMAND && !function_object( "main", cmd_ob ) ) {
    DEBUG( "Caling " + dump_value( cmd_ob ) +"->_main( " + ( arg ? ( "\"" + arg + "\"" ) : "<NIL>" ) + ", \"" + cmd + "\" )\n");
    cmd_ob->_main( arg, cmd );
    return 1;
  } else {
    string msg;
    msg = cmd + " not handled by the command daemon: " + dump_value( cmd_ob ) + "\n";
    msg += "Reason: ";
    if (!cmd_ob) {
      msg += "no matching .c file";
    } else if (!cmd_ob<-M_COMMAND) {
      msg += ".c file does not inherit m_command";
    } else if (function_object("main", cmd_ob)) {
      msg += "function main() is public";
    } else {
      msg += "unknown";
    }
    msg += "\n";
    DEBUG(msg);
    return -1;
  }
}

string cmdstats() {
  int i, sz;
  string r;
  string *syspath;

  if( !KERNEL() && !SYSTEM() ) {
    error("Permission denied.\n" );
  }

  syspath = map_indices( cmdpriv );
  r = "";

  for( i = 0, sz = sizeof( syspath ); i < sz; i++ ) {
    r += syspath[i] + " : " + sizeof( commands[syspath[i]] ) + "\n";
  }
  return r;
} 

int validate_path( string path ) {
  return access_check( path );
}

int cmd_path_exists( string path ) {
  return cmdpriv[path] ? 1 : 0;
}

/* can only be called from system code, which is trusted with this data
   especially since we return a copy so it can't be modified */
mapping query_cmdpriv() {
  if(!KERNEL() && !SYSTEM()) error("Permission denied");

  if(map_sizeof(cmdpriv)) {
    return cmdpriv[..];
  } else {
    return ([]);
  }
}

void add_path(string path, string priv) {
  if(!secure()) error("Permission denied.");
  if(path[0] != '/') error("Invalid path");
  if(path[strlen(path)-1] != '/') path += "/";
  cmdpriv[path] = priv;
  save_me();
}

void remove_path(string path) {
  if(!secure()) error("Permission denied.");
  cmdpriv[path] = nil;
  save_me();
}

