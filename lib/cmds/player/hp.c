void usage() {
   write("Usage: hp [-h]\n");
   write("A short way to display your current: hit points, mana, " +
      "endurance, ac\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
   if (str && str != "") {
      usage();
      return;
   }

   write("HP[" + this_player()->query_hp() + "/" +
      this_player()->query_max_hp() + "] " +
      "Mana[" + this_player()->query_mana() + "/" +
      this_player()->query_max_mana() + "] " +
      "Endurance[" + this_player()->query_end() + "/" +
      this_player()->query_max_end() + "] " +
      "AC [" + this_player()->query_defense() + "]");
}
