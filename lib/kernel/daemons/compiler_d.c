#include <privileges.h>
#include <tlsvar.h>


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

mixed include_file( string file, string path ) {
  if(path == "AUTO") {
    string * parts;
    parts = explode( DRIVER->get_tlvar(TLS_COMPILING), "/" );
    if(parts[0] == "kernel") {
      return "/kernel/include/std-kernel.h";
    } else {
      return "/kernel/include/std-game.h";
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

