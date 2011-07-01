// XXX combine with finger??? or just trash it? :)

void main( string str) {
  object *usr;
  int i;
  int flag;

  usr = users();
  flag = 0;

  for (i = 0; i < sizeof( usr ); i++) {
    if (usr[i]->query_player()->query_name() == str) {
      flag = 1;
      write( "%^BLUE%^Name:%^RESET%^ " + capitalize(usr[i]->query_player()->query_name()) + ".\n");
      write( "%^BLUE%^Title:%^RESET%^ " + usr[i]->query_player()->query_brief() + ".\n");
      write( "%^BLUE%^Description:%^RESET%^ " + usr[i]->query_player()->query_long() + "\n");
      if (usr[i]->query_player()->query_name()->query_admin() == 1) {
	write( "%^BLUE%^Status: %^RESET%^Administrator");
      } else { if (usr[i]->query_player()->query_name()->query_wiz() == 1) {
	write( "%^BLUE%^Status: %^RESET%^Wizard");}
      else { write( "%^BLUE%^Status: %^RESET%^Player");}};

      if (usr[i]->query_player()->query_idle() > 60) {
	write( "%^BLUE%^Idle: %^RESET%^" + format_time(usr[i]->query_player()->query_idle()) + "\n");
      }
      if (usr[i]->query_player()->query_name() != this_player()->query_name()) {
	usr[i]->query_player()->message( "You feel like someone is thinking about you.\n");
      }
    }
  } 
  
  if (file_exists("/data/players/" + str + ".o")) {
    flag = 1;
    write( capitalize(str) + " is currently absent.");
  }

  if (flag == 0) {
    write( capitalize(str) + " exists only in your dreams.\n");
  }  
}

