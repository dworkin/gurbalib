/*
 * Gurbalib command daemon
 *
 * by Aidil@Way of the Force
 *
 */

#define DATA_FILE "/sys/daemons/data/command_d.o"

#define DEBUG_COMMAND_D

mapping cmdpriv;
static mapping commands;

void rehash();

static void DEBUG( string str ) {
#ifdef DEBUG_COMMAND_D
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
      "/sys/cmds/admin/"     : "system",
      "/sys/cmds/wiz/"       : "wizard",
      "/cmds/player/"        : "*",
    ]);
  }

  save_me();
  rehash();
}

static int access_check( string path ) {
  return ( cmdpriv[path] == "*" ) || require_priv( cmdpriv[path] );
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

int exec_command( string cmd, string *syspath ) {
  string arg;
  object cmd_ob;
  int i, sz;

  DEBUG( "exec_command: " + ( cmd ? cmd:"<NIL>" ) + " " + dump_value( syspath ) + "\n");

  for( i = 0, sz = sizeof( syspath ); ( i < sz ) && !cmd_ob; i++ ) {
    DEBUG( "Locating " + cmd + " in " + syspath[i] + ": " );
    if( sizeof( commands[syspath[i]] & ({ cmd }) ) ) {
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
    DEBUG( cmd + " not handled by the command daemon: " + dump_value( cmd_ob ) + "\n" );
  }
}

string cmdstats() {
  int i, sz;
  string r;
  string *syspath;

  if( !require_priv( "system" ) ) {
    error("Permission denied.\n" );
  }

  syspath = map_indices( cmdpriv );
  r = "";

  for( i = 0, sz = sizeof( syspath ); i < sz; i++ ) {
    r += syspath[i] + " : " + sizeof( commands[syspath[i]] ) + "\n";
  }
  return r;
} 
