void main( string arg ) {

  string tmp;

  tmp = this_player()->query_env( "cwd" );

  this_player()->set_env( "cwd", this_player()->query_env( "pwd" ) );

  this_player()->set_env( "pwd", tmp );
  write( "%^BOLD%^" + this_player()->query_env( "cwd" ) + "%^RESET%^\n" );
}
