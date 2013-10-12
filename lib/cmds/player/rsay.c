inherit M_COMMAND;

void usage() {
   int x, max;
   string *langs;
   string *lines;

   lines = ({ "Usage: rsay [-h] [LANGUAGE] MSG" });
   lines += ({ "" });
   lines += ({ "Tell the current room MSG in a specific language." });
   lines += ({ "If no LANGUAGE is given, it uses your current race." });
   lines += ({ "Valid LANGUAGES are: " });

   langs = LANGUAGE_D->query_languages();
   max = sizeof(langs);
   for (x = 0; x < max; x++) {
      lines += ({ "\t" + langs[x] });
   }

   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\trsay catfolk Hi, are we being sneaky?" });
   lines += ({ "\trsay Can you read this?" });
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tbug, chan, echo, echoto, emote, shout, ssay, say, " +
         "sysmsg, tell, translate, whisper, wizcall" });
   } else {
      lines += ({ "\tbug, chan, emote, say, shout, tell, whisper, " +
         "wizcall" });
   }

   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }
 
   this_player()->more(lines);
}

static void tell_them(string str, string *words, string lang, string *words2) {
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
             if ((usr[i]->query_language() == lang) || 
                query_wizard(usr[i]) ||
                (x < usr[i]->query_skill("language/" + lang))) {
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

static void main(string str) {
   int i, k, x, kmax;
   string *words, *words2;
   string rest, first, lang;

   if (empty_str(str)) {
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
