#include <privileges.h>
#include <tlsvar.h>

#undef DEBUG_COMPILER_D
#undef STRICT_OBJECT_CHECKS

#define INHERIT_DIRS ({ "std", "lib" })
#define OBJECT_DIRS ({ "obj", "mon", "npc", "vendors", "objects", "monsters", "daemons", "rooms", "tmp", "cmds" })

static void create() {
  if(!get_list( "clones" )) {
    error(
      "Your config file is out of date.\n"+
      "Please change the line reading:\n"+
      "create = \"create\"\n"+
      "to\n"+
      "create = \"_F_create\"\n"+
      "or see the net.dgd/mud.dgd example config files\n"
    );
  }
  DRIVER->register_compiler_d();
}

private int test_path(string path, string * comp) {
  string * parts;
  int i, sz;

  parts = explode( path, "/" );
  for( i = 0, sz = sizeof( parts ) - 1; i < sz; i++ ) { 
    if( sizeof( parts[i..i] & comp ) > 0 ) {
      return 1;
    }
  }
  return 0;
}
  
int test_inheritable( string path ) {
  return test_path( path, INHERIT_DIRS );
}

int test_object( string path ) {
  return path == DRIVER || test_path( path, OBJECT_DIRS );
}

mixed include_file( string file, string path ) {
  if(path == "AUTO") {
    string * parts;
    string compiling;

    compiling = DRIVER->get_tlvar(TLS_COMPILING);
    parts = explode( compiling, "/" );

    if(parts[0] == "kernel") {
      /*
       * Don't do anything for auto objects
       *
       */
      if( sscanf(compiling, "/kernel/lib/auto%*s") == 0 ) {
        return "/kernel/include/std-kernel.h";
      }
    } else {
      if( compiling != "/sys/lib/auto" ) {
        return "/kernel/include/std-game.h";
      }
    }
  }

  if( path[0] != '/' ) {
    return file + "/../" + path;
  } else {
    return path;
  }
}


void register_includes(object by, string * what) {
  if(what && sizeof(what)) {
#ifdef DEBUG_COMPILER_D
    console_msg( object_name( by ) + " includes " + dump_value( what, ([]) ) + "\n" );
#endif
  }
}

void register_inherits(object by, object * what) {
  if(what && sizeof(what)) {
#ifdef DEBUG_COMPILER_D
    console_msg( object_name( by ) + " inherits " + dump_value( what, ([]) ) + "\n" );
#endif
  }
}

mixed allow_compile(string path, string file) {
  if(path == "/sys/lib/auto") {
    string * files;
    string * code;
    int i, sz;

    console_msg("allow_compile: "+path+"\n");
    code = ({ "inherit \"/kernel/lib/auto-game\";" });
    files = get_dir("/sys/safun/*.c")[0];
    if(files) {
      for( i = 0, sz=sizeof(files); i<sz; i++ ) {
        code += ({ "#include \"/sys/safun/"+files[i]+"\"" });
      }
    }
#ifdef DEBUG_COMPILER_D
    console_msg("Dumping safun object:\n\n"+implode(code,"\n")+"\n\n");
#endif
    return code;
  } else {
    return path;
  }
}

string allow_inherit(string path, string file) {
  if( !test_inheritable( path ) ) {
#ifndef STRICT_OBJECT_CHECKS
    console_msg("WARNING: inheriting a program that is not in an inheritable dir : " + path + "\n" );
#else
    error(path + " is not inheritable");
#endif
  }
  return path;
}

string allow_object(string path) {
  if( !test_object( path ) ) {
#ifndef STRICT_OBJECT_CHECKS
    console_msg("WARNING: " + path + " is used as an object, but doesn't come from an object dir!\n" );
#else
    error(path + " is not an object");
#endif
  }
  return path;
}
