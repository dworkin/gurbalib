void main( string str){

  int ac;

  ac = this_player()->query_defense();

  this_player()->message( "%^CYAN%^AC: " + ac + "%^RESET%^");
}
