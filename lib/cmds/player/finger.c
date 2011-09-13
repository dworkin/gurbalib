void usage() {
  write("Usage: finger [-h] PLAYER\n");
  write("Look up information about the given player PLAYER.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str) {
  if (!str || str == "") {
     usage();
     return;
  }

  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }
    
  str = lowercase(str);

  if (USER_D->player_exists(str)) {
     USER_D->finger(this_player(), str);
  } else {
    write( capitalize(str) + " exists only in your dreams.\n");
  }  
}
