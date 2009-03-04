/* Catfolk can communicate with other catfolk without other races almost
	 even noticing. They can, however, only talk one word at a time. */

void main( string str ) {
	object *usr;
	string dummy;
  int i;
  
	/* Strip trailing whitespaces */
  for( i=strlen(str)-1; i > 0; i-- ) {
    if( str[i] != ' ' )
      break;
    str = str[0..(i-1)];
  }
  /* You can only send one word at a time :) */
	/* It would be nice if there was a way of preventing a message like:
		 WatchOutFudgeIsHereAndWantsToStealYourMoneySoYouBetterBeCareful
		 Maybe a set limit of like 5 characters to be transmitted? */
	sscanf(str, "%s %s", str, dummy);

  if (str != "") {

  	str = capitalize(str);

	  usr = USER_D->query_users();
  	for ( i = 0; i < sizeof (usr); i++) {
    	if (((usr[i]->query_environment() == this_environment()) && usr[i]->query_race() == "catfolk" )) {
				usr[i]->message( capitalize(this_player()->query_name()) + " secretly tells you: " + str + "\n");
				write( "You secretly communicate: " + str + "\n");
			} else if (usr[i]->query_environment() == this_environment() ) {
				usr[i]->message( capitalize(this_player()->query_name() + "'s ears twitch briefly.\n"));
			}
		}
	}
}
