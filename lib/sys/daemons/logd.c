int minlevel;
mapping special_logs;

static void save_me() {
  unguarded( "save_object", "/sys/data/logd.o" );
}

static void restore_me() {
  unguarded( "restore_object", "/sys/data/logd.o" );
}

static void create() {
  restore_me();

  if( !special_logs ) {
    special_logs = ([
      "compile" : "errors/compile",
      "runtime" : "errors/runtime",
    ]);

    minlevel = 3;
    save_me();
  }
}

void write_log( string log, string message, varargs int level ) {
  string basedir;
  string user;

  user = owner_object( previous_object() );

  if( sscanf( log, "%*s/..%*s" ) != 0 ) {
    error( "illegal log name" );
  }

  if( !level ) {
    level = 3;
  }

  switch( user ) {
    case "system" :
    case "kernel" :
    case "game"   :
      basedir = "/logs/";
      break;
    default : 
      if( unguarded( "file_exists", "/wiz/" + user ) == -1 ) {
        basedir = "/wiz/" + user + "/logs/";
      } else if( unguarded( "file_exists", "/domains/" + user ) == -1 ) {
        basedir = "/domains/" + user + "/logs/";
      } else {
        basedir = "/logs/nobody/";
      }
      break;
  }

  if( special_logs[log] ) {
    log = special_logs[log];
  }

  unguarded( "write_file", basedir + log, message );
}
