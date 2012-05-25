void usage() {
   int x, max;
   string *langs;

   write("Usage: rsay [-h] [LANGUAGE] MSG\n");
   write("Tell the current room MSG in a specific language.\n");
   write("If no LANGUAGE is given, it uses your current race.\n");
   write("Valid LANGUAGES are: ");

   langs = LANGUAGE_D->query_languages();
   max = sizeof(langs);
   for (x = 0; x < max; x++)
      write("\t" + langs[x] + "\n");

   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: say, tell, whisper, translate\n");
}

// XXX Need to fix this so it works, and also works off of skills/race....

void main(string str) {
   object *usr;
   int i, k;
   string *words;
   string tmp, rest, first, race;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   race = "";

   if (sscanf(str, "%s %s", first, rest) == 2) {
      if (LANGUAGE_D->valid_language(first)) {
	 race = first;
	 str = rest;
      }
   }

   if (race == "") {
      race = this_player()->query_race();
      if (!LANGUAGE_D->valid_language(race))
	 race = "";
   }
   if (race == "") {
      this_environment()->tell_room(this_player()->query_Name() + 
         " makes an undescribable noise.\n");
      write("Error, invalid race.\n");
      return;
   }

   for (i = strlen(str) - 1; i > 0; i--) {
      if (str[i] != ' ')
	 break;
      str = str[0..(i - 1)];
   }

   if (str != "") {
      str = lowercase(str);

      words = explode(str, " ");
      for (k = 0; k < sizeof(words); k++) {
	 /*Translate it to cat */
	 words[k] = LANGUAGE_D->english_to_racial(race, words[k]);
      }
      usr = USER_D->query_players();
      for (i = 0; i < sizeof(usr); i++) {
	 if ((usr[i]->query_environment() == this_player()->query_environment())
	    && (usr[i]->query_race() == race) && (usr[i] != this_player())) {
	    usr[i]->message(this_player()->query_Name() +
	       " says in " + race + " tongue: " + str + "\n");
	 }
	 if ((usr[i]->query_environment() == this_player()->query_environment())
	    && (usr[i]->query_race() != race) && (usr[i] != this_player())) {
	    usr[i]->out(this_player()->query_Name() + " says:");
	    for (k = 0; k < sizeof(words); k++) {
	       usr[i]->out(" " + words[k]);
	    }
	    usr[i]->out(" \n");
	 }
      }
      write("You say in " + race + ": " + str + "\n");
   }
}
