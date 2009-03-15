#include <privileges.h>

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
    parts = explode( file, "/" );
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
