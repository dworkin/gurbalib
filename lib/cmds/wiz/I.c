void usage() {
  write("Usage: I [-h] MSG\n");
  write("Record a did MSG message, whatever that is....\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

// XXX Figure out what this is used for... it stores an entry in 
//     daemons/data/did_d.o   what the heck is it though????

void main( string str ) {
  if (!str || str == "") {
     usage();
     return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  DID_D->add_entry( str );
}
