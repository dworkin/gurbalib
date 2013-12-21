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
   lines += ({ "\tinventory, junk, levels, score, skills" });

   this_player()->more(lines);
}

static void main(string str) {
   string line;
   if (!empty_str(str)) {
      usage();
      return;
   }

   line = this_player()->get_status(this_player());
   write(line);
}
