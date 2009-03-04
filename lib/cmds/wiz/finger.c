void main( string str) {
  object *players;
  int i;
  object player;
  int cloned;
  int found;
  
  if (str != "") {
    
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
      player = clone_object( "/std/player" );
      player->set_name( str );
      player->restore_me();
      found = 1;
      cloned = 1;
    }    
    
    if (found == 1) {;
    write( "%^BLUE%^Name:%^RESET%^ " + capitalize(player->query_name()) + ".\n");
    write( "%^BLUE%^Title:%^RESET%^ " + player->query_title() + ".\n");
    write( "%^BLUE%^Description:%^RESET%^ " + player->query_long() + "\n");
    if (SECURE_D->query_admin(player->query_name()) == 1){ 
      write( "%^BLUE%^Status: %^RESET%^Administrator\n");}
    else if (SECURE_D->query_wiz(player->query_name()) == 1) {
      write( "%^BLUE%^Status: %^RESET%^Wizard\n");}
    else {
      write( "%^BLUE%^Status: %^RESET%^Player\n");};
    if (cloned != 1 && this_player()->query_name() == "aphex") {
      write( "%^BLUE%^Hit points: %^RESET%^" + player->query_hp() + "/" + player->query_max_hp() + "\n" );
    }
    write( "%^BLUE%^Real name: %^RESET%^" + player->query_real_name()  + "\n");
    write( "%^BLUE%^Email address: %^RESET%^" + player->query_email_address() + "\n");
    if (player->query_idle() > 60) {
      write( "%^BLUE%^Idle: %^RESET%^" + format_time(player->query_idle()) + "\n");
    }
    if (cloned == 1) {
      write( "%^BLUE%^Last login: %^RESET%^" + ctime(player->query_last_login()) );
    }
    
    if ((player->query_name() != this_player()->query_name()) /*&& !SECURE_D->query_wiz(this_player()->query_name()) > 0*/ && cloned != 1) {
      player->message( "You feel like someone is thinking about you.\n");
    }
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