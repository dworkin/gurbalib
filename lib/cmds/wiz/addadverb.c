void usage() {
  write("Usage: addadverb [-h] ADVERB\n");
  write("Add an adverb: ADVERB.\n");

// XXX Need to flesh out help here.... what is this how do you view adverbs?

  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  if( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  EMOTE_D->add_adverb( lowercase(str) );
  write( "Addverb added.\n" );
}
