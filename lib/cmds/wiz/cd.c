void usage() {
  write("Usage: cd [-h] [dir]\n");
  write("Change the current working directory(cwd) to [dir].\n" +
    "If [dir] is not given, the working directory is set to the wizards\n" +
    " home directory.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("Examples:\n");
  write("cd /cmds         Change cwd to the /cmds directory.\n");
  write("cd ..            Move up one directory.\n");
  write("cd               Change cwd to /wiz/(username).\n");
  write("See also: pwd, ls, browse\n");
}

void main( string arg ) {
  if (!arg || arg == "") {
	arg = "/wiz/" + this_player()->query_name();
  }

  arg = normalize_path( arg, this_player()->query_env( "cwd" ) );

  if( !arg || arg == "" ) {
    write( "Access denied.\n" );
    return;
  }
  
  if( strlen(arg) > 1 && arg[strlen(arg)-1] == '/' ) {
    arg = arg[..strlen(arg)-2];
  }
    
  if( file_exists( arg ) != -1 ) {
    write( "Dir not found.\n" );
    return;
  }

  this_player()->set_env( "cwd", arg );
  this_player()->set_env( "pwd", this_player()->query_env( "cwd" ) );
  write( "%^BOLD%^" + this_player()->query_env( "cwd" ) + "%^RESET%^\n" );
}
