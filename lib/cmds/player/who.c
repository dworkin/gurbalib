void usage() {
  if (query_wizard(this_player())) {
     write("Usage: people [-h] [-l]\n");
     write("Print out a list of who is on the system.\n");
     write("Options:\n");
     write("\t-h\tHelp, this usage message.\n");
     write("\t-l\tLong listing which shows additional info.\n");
   
  } else {
     write("Usage: people [-h]\n");
     write("Print out a list of who is on the system.\n");
     write("Options:\n");
     write("\t-h\tHelp, this usage message.\n");
  }
}

// XXX Maybe just remove the -l option... if we don't add other stuff
//   just make it the default

/*
  'who' command
  Originally by Fudge
  Improved by Cerihan 3/15/09
*/

void main( string str ) {
  object *usr;
  int i;
  int LONG;
  mixed idletime;
  string idle;

  LONG = 0;
  if (sscanf(str, "-%s",str)) {
    if (str == "l") {
      LONG = 1;
    } else {
       usage();
       return;
    }
  } else if (str && str != "") {
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
    idletime = format_time(usr[i]->query_idle());
    if (idletime == "")  {
        idle = "";
    } else {
        idle = "  (idle " + idletime + ")";
    }
    line += idle;

    if (LONG == 1) {
       write(line + "\n\t" + usr[i]->query_environment()->query_brief() + "\n");
    } else {
       write(line + "\n");
    }
  }
  write("------------------------------------------------------");
}

