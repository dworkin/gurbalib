void usage() {
  write("usage: pwd [-h]\n");
  write("Prints the current working directory.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  write( "%^BOLD%^" + this_player()->query_env("pwd") + "%^RESET%^\n" );
}
