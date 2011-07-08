void usage() {
  write("Usage: ssay [-h] WHO WHAT\n");
  write("Say WHAT to WHO XXX.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  int i;
  string how; /*It's not what you say, but how you say it...*/
  string what; /*But what you say is important too.*/
  /* Strip trailing whitespaces */

  for ( i=strlen(str)-1; i > 0; i-- ) {
    if ( str[i] != ' ' )
      break;
    str = str[0..(i-1)];
  }

  if (sscanf(str, "%s|%s", how, what) != 2) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if (str != "") {
    
    switch(what[strlen(what)-1]) {
    case '.' :
    case '?' :
    case '!' :
    case ',' :
      break;
    default:
      what += ".";
    }
    
    this_player()->query_environment()->tell_room( nil,"%^GREEN%^" + capitalize(this_player()->query_name()) + " " + how +": %^RESET%^" + capitalize(what) + "\n" );
  } else {
     usage();
     return;
  }
}
