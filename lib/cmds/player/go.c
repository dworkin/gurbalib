void usage() {
  write("Usage: go [-h] DIRECTION\n");
  write("Allows you to move in the specified direction.  To see where you\n");
  write("can go, \"look\" around.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  string error;
  string str2;
  int len;

   if ( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str) || sscanf(str, "%s -%s",str,str2)) {
     usage();
     return;
  }

  len = strlen(str);
  if (str[len-1] == ' ') str = str[..len-2];

  error = this_environment()->body_exit( this_player(), str );

  if( error ) write( error );
}

