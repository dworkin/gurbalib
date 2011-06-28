void usage() {
  write("Usage: echoto [-h] [player] MSG\n");
  write("Echo a message MSG to the player specified.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string who ) {
  object *usr;
  int i;
  int flag;
 
  string msg;

  if (!who || (who == "")) {
     usage();
     return;
  }

  if (sscanf(who, "-%s",who)) {
     usage();
     return;
  }

  sscanf( who, "%s %s", who, msg );

  usr = users();
  flag = 0;
  for( i = 0; i < sizeof( usr ); i++) {
    if( usr[i]->query_name() == who ) {
      usr[i]->query_player()->message( "\n" + msg + "\n");
      write( "You echo to " + who + ": '" + msg + "'\n");
      flag = 1;
    }
  }
  
  if (flag == 0) {
    write( "You can't find " + who + ".\n" );
  }
}
