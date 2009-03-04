void main(string arg) {
   string race;
   string englishword;
   englishword = arg;
   race = "catfolk";
   write(englishword + "\n");
   write(LANGUAGE_D->english_to_racial(race, englishword));
}

