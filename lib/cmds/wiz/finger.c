void usage() {
  write("Usage: finger [-h] PLAYER\n");
  write("Look up information about the given player PLAYER.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str) {
  object *players;
  int i;
  object player;
  int cloned;
  int found;
  
  if (str != "") {
    if (sscanf(str, "-%s",str)) {
       usage();
       return;
     }
    
    players = USER_D->query_players();
    cloned = found = 0;
    
    str = lowercase(str);
    
    for (i = 0; i < sizeof( players ); i++) {
      if (players[i]->query_name() == str) {
	player = players[i];
	found = 1;
      }
    }
    if (found != 1 && file_exists( "/data/players/" + str + ".o")) {
      write( "%^RED%^" + capitalize(str) + " is not logged in.%^RESET%^");
      player = clone_object( PLAYER_OB );
      player->set_name( str );
      player->restore_me();
      found = 1;
      cloned = 1;
    }    
    
    if (found == 1) {;
    write( "%^BLUE%^Name:%^RESET%^ " + capitalize(player->query_name()) + ".\n");
    write( "%^BLUE%^Title:%^RESET%^ " + player->query_title() + ".\n");
    write( "%^BLUE%^Description:%^RESET%^ " + player->query_long() + "\n");
    if ( query_admin(player->query_name()) == 1 ){ 
      write( "%^BLUE%^Status: %^RESET%^Administrator\n");}
    else if( query_wizard( player->query_name() ) == 1 ) {
      write( "%^BLUE%^Status: %^RESET%^Wizard\n");}
    else {
      write( "%^BLUE%^Status: %^RESET%^Player\n");};
    }
    write( "%^BLUE%^Real name: %^RESET%^" + player->query_real_name()  + "\n");
    write( "%^BLUE%^Email address: %^RESET%^" + player->query_email_address() + "\n");
    if (player->query_idle() > 60) {
      write( "%^BLUE%^Idle: %^RESET%^" + format_time(player->query_idle()) + "\n");
    }
    if (cloned == 1) {
      write( "%^BLUE%^Last login: %^RESET%^" + ctime(player->query_last_login()) );
    }
    
    if ((player->query_name() != this_player()->query_name()) /*&& !query_wizard(this_player()->query_name()) > 0*/ && cloned != 1) {
      player->message( "You feel like someone is thinking about you.\n");
    }

    if (found != 1) {
      write( capitalize(str) + " exists only in your dreams.\n");
    }  
    
    if (cloned == 1) {
      destruct_object( player );
    }
  } else {
    write( "You wanna give WHO the finger?" );
  }
}
