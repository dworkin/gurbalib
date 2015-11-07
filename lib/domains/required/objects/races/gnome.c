/* Definition of the gnome race */
inherit "/std/race";

void create(void) {
   ::create();

   set_race_short_desc("Gnomes are the brainy brothers of the dwarves..");
   set_race_long_desc("Gnomes are a strange folk. Most humans would call " +
      "them freaks. Always\ntoying with inventions, strange devices, or " +
      "mysterious summonings, rarely \na day goes by in a gnome community " +
      "without some sort of explosion or monster \non the loose. Yet they " +
      "keep continuing. Gnomes seem obsessed with investigating\n" +
      "and finding out of things they come across - often with disastrous " +
      "results.");
   set_language("gnomish");
   set_skill("language/gnomish", 100);
}
