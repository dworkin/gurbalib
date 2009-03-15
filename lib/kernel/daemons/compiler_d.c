#include <privileges.h>

static void create() {
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
