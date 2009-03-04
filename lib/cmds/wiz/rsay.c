void main(string str) {
	object *usr;
  int i, k;
  string *words;
  string race;
  string tmp;
  for( i=strlen(str)-1; i > 0; i-- ) {
  if( str[i] != ' ' )
  	break;
  str = str[0..(i-1)];
  }
  race = "catfolk";
  if (str != "") {
     str = lowercase(str);
     
     words = explode(str, " ");
     for ( k = 0; k < sizeof (words); k++) {
	words[k] = LANGUAGE_D->english_to_racial(race, words[k]); /*Translate it to cat*/
     }
     usr = USER_D->query_players();
     for ( i = 0; i < sizeof (usr); i++) {
	if ((usr[i]->query_environment() == this_player()->query_environment()) && (usr[i]->query_race() == "catfolk") && (usr[i] != this_player()) ) {
	   usr[i]->message( capitalize(this_player()->query_name()) + " says in cattongue: " + str + "\n");
	}
	if ((usr[i]->query_environment() == this_player()->query_environment()) && (usr[i]->query_race() != "catfolk") && (usr[i] != this_player()) ) {
	   usr[i]->out( capitalize(this_player()->query_name()) + " says:");
	   for (k = 0; k < sizeof (words); k++) {
	      tmp = usr[i]->catfolk_to_english(words[k]);
	      usr[i]->out( " " + tmp );
	   }
	   usr[i]->out(" \n");
	}
     }
     write( "You meow: " + str + "\n");
  }
}
