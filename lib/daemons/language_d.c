/* See /help/wiz/language_d for some explanations */
mapping catfolk_dic; 
mapping dwarf_dic;
mapping human_dic;
static string transword;

static void restore_me( void ) {
   unguarded( "restore_object", "/daemons/data/language_d.o" );
}

void create( void ) {
   catfolk_dic = ([ ]);
   human_dic = ([ ]);
   dwarf_dic = ([ ]);

   /* Ok so I hate making up words... :) */
   /* These are just so that the mappings have something in them */
   catfolk_dic += ([ "zifges" : "gesbfe" ]); 
   dwarf_dic += ([ "zifges" : "gesfbe" ]);
   human_dic += ([ "zifges" : "gefffe" ]);

   restore_me();
}

static void save_me( void ) {
   unguarded( "save_object", "/daemons/data/language_d.o" );
}

string random_word(string race) {
	int num_words; /* Number of catfolk words in the 'english word' */
	int k;
	string words; /*What's gonna be returned */
	if (race == "catfolk") {
		words = "";
		num_words = random(3) + 1;
		for (k=0; k < num_words; k++) {
			switch (random(15) + 1) {
				/* Feel free to add more stuff here */
				case 1 : words += "meow ";
					break;
				case 2 : words += "hiss ";
					break;
				case 3 : words += "purr ";
					break;
				case 4 : words += "weow ";
					break;
				case 5 : words += "s'fel ";
					break;
				case 6 : words += "m'naf ";
					break;
				case 7 : words += "myau ";
					break;
				case 8 : words += "myaw ";
					break;
				case 9 : words += "nyee ";
					break;
				case 10: words += "rakas ";
					break;
				case 11: words += "krss ";
					break;
				case 12: words += "rrr"; /*I know these two lack spaces*/
					break;
				case 13: words += "ssss"; /*It's supposed to be that way*/ 
					break;
				case 14: words += "clsss ";
					break;
				case 15: words += "mn ";
					break;
				}
			}
			words[strlen(words)-1] = 0; /*Strip the trailing space*/
			return words;		
	} else if (race == "dwarf") {
		return race;
		/* Make code for returning a random Norwegian word here */
	} else {
		return race; /*DEBUG ALERT!!!!*/
	}
}

string add_racial(string language, string englishword) {
   englishword = lowercase(englishword);
   write(language);
   write(englishword);
   if (language == "catfolk") {
      if( !(catfolk_dic[englishword]) ){
         transword = random_word(language);
         catfolk_dic += ([ englishword : transword ]);
         return transword;
      }
   } else if (language == "dwarf") {
      if( !(dwarf_dic[englishword]) ) {
	 write("!(dwarf_dic[" + englishword + "])");
         transword = random_word(language);
         dwarf_dic += ([ englishword : transword ]);
         return transword;
      }
   }
}

/*This here is the main function. It must be called for each word to be
  translated. If the word doesn't exist in the dictionary, then
  add_catfolk() will automatically be called from here. This function will
  return the catfolk word corresponding to the english word fed into it.
*/
string english_to_racial(string language, string arg) {
   string englishword;
   englishword = lowercase(arg);
   if (language == "catfolk") {
      if ( member_map(englishword, catfolk_dic) ) {
         return catfolk_dic[englishword];
      }
   } else if (language == "human") {
      if ( member_map(englishword, human_dic) ) {
         return human_dic[englishword];
      }
   } else if (language == "dwarf") {
      write("In 'if language == dwarf'");
      if ( member_map(englishword, dwarf_dic) ) {
	 write("It's a member");
         write(englishword);
	 write(dwarf_dic[englishword]);  
	 return dwarf_dic[lowercase(englishword)];
      } else {
	 write ("it's not a member");
      }
   }
   /* We didn't find it, so we must add it */
   return add_racial(language, englishword);
   /* We return it at the same time :) */
}

string *query_languages() {
	string *langs;
	langs = ({ });
	langs += ({ "catfolk" });
	langs += ({ "dwarven" });

	return langs;
}

int valid_language(string str) {
   switch(str) {
      case "catfolk":
      case "dwarven":
         return 1;
         break;
      default:
         return 0;
         break;
   }
}
