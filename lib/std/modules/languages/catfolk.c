/* Module to allow players to translate from catfolk to english */
mapping catfolk_words;      /* ([ "meow":"Hello","prrr":"die" ]) */

string catfolk_to_english(string arg) {
   string translated_word;
   string catword;
   catword = arg;
   if (!(catfolk_words)) {
      catfolk_words = ([]);
   }
   /* catword = lowercase(catword); */
   if (member_map(catword, catfolk_words)) {    /*If it is in the vocabulary */
      translated_word = catfolk_words[catword];
      return translated_word;
   } else {
      return catword;
   }
}

void learn_catfolk_word(string catword, string englishword) {
   if (!(catfolk_words)) {
      catfolk_words = ([]);
   }
   catword = lowercase(catword);
   englishword = lowercase(englishword);
   /* catfolk_words -= ([ catword ]); */
 catfolk_words += ([catword:englishword]);
   /* write("Word learned: " + catword + " meaning " + englishword ".\n");  */
}
