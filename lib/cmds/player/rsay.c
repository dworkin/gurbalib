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

void main(string str) {
   object *usr;
   int i, k, x, kmax;
   string *words, *words2;
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
   words2 = ({ });

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
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " makes an undescribable noise.\n");
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
      kmax = sizeof(words);
      for (k = 0; k < kmax; k++) {
         x = random(100) + 1;
         if (x < this_player()->query_skill("language/" + race)) {
  	    /*Translate it to cat */
	    words2 += ({ LANGUAGE_D->english_to_racial(race, words[k]) });
         } else {
            /*Mess up the word... */
	    words2 += ({ LANGUAGE_D->random_word(race) });
            words= words2;
         }
      }
      usr = USER_D->query_players();
      for (i = 0; i < sizeof(usr); i++) {
         if (usr[i] == this_player()) {
            write("You say in " + race + ": " + str + "\n");
         } else if ((usr[i]->query_race() == race) || 
            USER_D->query_wizard(usr[i])) { 
	    usr[i]->message(this_player()->query_Name() +
	       " says in " + race + " tongue: " + str + "\n");
	 } else {
            tmp = "";
	    for (k = 0; k < sizeof(words); k++) {
               x = random(100) + 1;
               if (x < usr[i]->query_skill("language/" + race)) {
                  tmp = tmp + words[k] + " ";
               } else {
                  tmp = tmp + words2[k] + " ";
               }
	    }
	    usr[i]->message(this_player()->query_Name() + 
               " says in " + race + " tongue: " + tmp + "\n");
	 }
      }
   }
}
