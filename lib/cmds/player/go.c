void usage() {
  write("Usage: go [-h] DIRECTION\n");
  write("Allows you to move in the specified direction.  To see where you\n");
  write("can go, \"look\" around.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  string error;

   if ( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  error = this_environment()->body_exit( this_player(), str );

  if( error ) write( error );
}

