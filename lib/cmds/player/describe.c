void usage() {
  write("Usage: describe [-h] DESCRIPTION\n");
  write("Allows you to change your DESCRIPTION, so that when someone looks " +
    "at you,\nThey know what you look like.");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {

  if (!str || str == "") {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
    usage();
    return;
  }

  if( str ) {
    str = replace_string( str, "$N", this_player()->query_proper_name() );
  }

  this_player()->set_long( str );
  this_player()->simple_action( "$N $vchange $p looks." );
}
