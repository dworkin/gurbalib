void usage() {
  write("Usage: wall [-h] MSG\n");
  write("Tell everyone on the mud: MSG.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("\t-w\tRestrict the MSG to sending only to wizards, " +
    "not normal players.\n");
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

  // XXX Do the wall here...
} 

