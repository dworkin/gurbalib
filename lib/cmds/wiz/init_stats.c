void usage() {
  write("Usage: init_stats [-h]\n");
  write("Initialize your stats.  Not sure why you need to or would want to " +
    "do this.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  if (str && str != "" ) {
    usage();
    return;
  }

  this_player()->initialize_stats();
  write("stats initialized!\n");
}
