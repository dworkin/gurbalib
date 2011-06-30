void usage() {
  write("usage: pwd [-h]\n");
  write("Prints the current working directory.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: cd, ls, browse\n");
}

void main( string str ) {
  if (str && (str != "")) {
    usage();
  } else {
    write( "%^BOLD%^" + this_player()->query_env("pwd") + "%^RESET%^\n" );
  }
}
