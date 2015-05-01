/* Module to allow players to translate from racial to english */
mapping racial_words;             /* ([ "meow":"Hello","dø":"die" ]) */

string racial_to_english(string racialword) {
   if (!(racial_words)) {
      racial_words = ([]);
   }
   racialword = lowercase(racialword);
   if (racial_words[racialword]) {       /*If it is in the vocabulary */
      return racial_words[racialword];
   } else {
      return racialword;
   }
}

void learn_racial_word(string racialword, string englishword) {
   if (!(racial_words)) {
      racial_words = ([]);
   }
   if (racialword) {
      racialword = lowercase(racialword);
   }
   if (englishword) {
      englishword = lowercase(englishword);
   }
   racial_words[racialword] = nil;

 racial_words += ([racialword:englishword]);
   write("Word learned: " + racialword + " meaning " + englishword + ".\n");
}
