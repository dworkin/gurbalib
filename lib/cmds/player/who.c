void usage() {
   write("Usage: who [-h]\n");
   write("Print out a list of who is on the system.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   if (query_wizard(this_player())) {
      write("See also: last\n");
   }
}

/*
  'who' command
  Originally by Fudge
  Improved by Cerihan 3/15/09
*/

void main( string str ) {
  object *usr;
  int i;
  int long_flag;
  mixed idletime;
  string idle;

  if (query_wizard(this_player())) {
     long_flag = 1;
  } else {
     long_flag = 0;
  }
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
    idletime = format_time(usr[i]->query_idle());
    if (idletime == "")  {
        idle = "";
    } else {
        idle = "  (idle " + idletime + ")";
    }
    line += idle;

    if (long_flag == 1) {
       write(line + "\n\t" + usr[i]->query_name() + " is: " + 
          usr[i]->query_environment()->query_brief() + "\n");
    } else {
       write(line + "\n");
    }
  }
  write("------------------------------------------------------");
}

