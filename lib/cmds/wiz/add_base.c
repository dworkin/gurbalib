void usage() {
  write("Usage: add_base [-h] STATNAME\n");
  write("Increase stat STATNAME by 1.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: stats, add_bonus\n");
}


void main( string statname ) {
   if( !statname || statname == "" ) {
     usage();
     return;
  }
  if (sscanf(statname, "-%s",statname)) {
     usage();
     return;
  }

  this_player()->add_base_stat(statname, 1);
  write("done!\n");
}

