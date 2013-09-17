inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: hp [-h]" });
   lines += ({ "" });
   lines += ({ "A short way to display your current: hit points, mana, " +
      "endurance, ac" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\thp" });
   lines += ({ "See also:" });
   lines += ({ "\tinventory, levels, score, skills" });

   this_player()->more(lines);
}

static void main(string str) {
   if (str && (str != "")) {
      usage();
      return;
   }

   write("HP [" + this_player()->query_hp() + "/" +
      this_player()->query_max_hp() + "] " +
      "Mana [" + this_player()->query_mana() + "/" +
      this_player()->query_max_mana() + "] " +
      "Endurance [" + this_player()->query_end() + "/" +
      this_player()->query_max_end() + "] " +
      "AC [" + this_player()->query_defense() + "]");
}
