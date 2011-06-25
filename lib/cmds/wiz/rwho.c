void usage() {
  write("Usage: rwho [-h] MUDNAME\n");
  write("Remote who, lists users on another mud.\n");
  write("To see what other muds you can look at use the command: mudlist\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  if( !str || str == "" ) {
    write( "Usage: rwho mudname\n" );
    usage();
    return;
  }
  if (sscanf(str, "-%s", str) ) {
    usage();
    return;
  }

  IMUD_D->do_who( str );
}
