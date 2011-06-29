void usage() {
  write("Usage: trans [-h] PLAYER\n");
  write("Find PLAYER, and then transport them to you.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

/*Made by Aphex on Fri 21 Nov 97*/
void main (string str) {
  object usr;
  object player;
  
  if(!str || str == "") {
    write( "Usage: trans <player>" );
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  usr = USER_D->find_user(str);
  if (usr) {
    player = usr->query_player();
    if (this_player()->query_environment() != 
	player->query_environment()) {

      player->query_environment()->tell_room( 
         player, 
         capitalize(player->query_name()) + " disappears.\n"
      );
      player->move(
         this_player()->query_environment()->base_name()
      );
      player->query_environment()->tell_room( 
         player, 
         capitalize(player->query_name())+" suddenly appears.\n");
      player->message( "\nYou are magically transported to " + capitalize(this_player()->query_name()) +".\n");
    } else {
      out("That player is already here.\n");
    } 
  } else {
    out( capitalize(str) + " not found.\n");
  }
}


