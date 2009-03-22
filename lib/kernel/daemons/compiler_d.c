#include <privileges.h>
#include <tlsvar.h>

#undef DEBUG_COMPILER_D


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
  return path;
}

