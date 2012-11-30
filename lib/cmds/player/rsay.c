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
   write("Examples:\n");
   write("\trsay catfolk Hi, are we being sneaky?\n");
   write("\trsay Can you read this?\n");
   if (query_wizard(this_player())) {
      write("See also: emote, say, shout, ssay, tell, translate, whisper\n");
   } else {
      write("See also: emote, say, shout, tell, whisper\n");
   }
}

tell_them(string str, string *words, string lang, string *words2) {
   object *usr;
   int i, imax, k, kmax, x;
   string tmp;

   usr = USER_D->query_players();
   imax = sizeof(usr);
   for (i = 0; i < imax; i++) {
      if (usr[i] == this_player()) {
         write("You say in " + lang + ": " + str + "\n");
      } else {
         tmp = "";
         kmax = sizeof(words);
	 for (k = 0; k < imax; k++) {
             x = random(100) + 1;
             if (usr[i]->query_language() == lang || usr[i]->query_wizard() ||
                x < usr[i]->query_skill("language/" + lang)) {
                tmp = tmp + words[k] + " ";
             } else {
                tmp = tmp + words2[k] + " ";
             }
	  }

         usr[i]->message(this_player()->query_Name() + 
            " says in " + lang + ": " + tmp + "\n");
      }
   }
}

void main(string str) {
   int i, k, x, kmax;
   string *words, *words2;
   string rest, first, lang;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   lang = "";
   words2 = ({ });

   if (sscanf(str, "%s %s", first, rest) == 2) {
      if (LANGUAGE_D->valid_language(first)) {
	 lang = first;
	 str = rest;
      }
   }

   if (lang == "") {
      lang = this_player()->query_language();
      if (!LANGUAGE_D->valid_language(lang))
	 lang = "";
   }
   if (lang == "") {
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " makes an indescribable noise.\n");
      write("You say: " + str + "\n");
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

      if (lang == "english") {
         tell_them(str, words, lang, words);
      } else {
         kmax = sizeof(words);
         for (k = 0; k < kmax; k++) {
            x = random(100) + 1;
            if (x < this_player()->query_skill("language/" + lang)) {
  	       /*Translate it to cat */
	       words2 += ({ LANGUAGE_D->english_to_racial(lang, words[k]) });
            } else {
               /*Mess up the word... */
	       words2 += ({ LANGUAGE_D->random_word(lang) });
               words= words2;
            }
         }

         tell_them(str, words, lang, words2);
      }
   }
}
