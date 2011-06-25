void usage() {
  write("Usage: people [-h]\n");
  write("Print out a list of who is on the system.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

// XXX  merge with the wizard people command... lets reduce commands
//      people need to use...

/*
  'who' command
  Originally by Fudge
  Improved by Cerihan 3/15/09
*/

void main( string str ) {
  object *usr;
  int i;

  if (str && str != "") {
     usage();
     return;
  }

  usr = players();
  
  write(MUD_NAME + " currently has " + sizeof( usr ) + " users online."); 
  write("------------------------------------------------------");
  for( i = 0; i < sizeof( usr ); i++) {
    string line;
    line = capitalize(usr[i]->query_title());
    if ( query_admin( usr[i] ) ) {
      line += " %^BOLD%^%^BLUE%^(Admin)%^RESET%^";
    }
    else if ( query_wizard( usr[i] ) ) {
      line += " %^CYAN%^(Wizard)%^RESET%^";
    }
    write(line + "\n");
  }
  write("------------------------------------------------------");
}

