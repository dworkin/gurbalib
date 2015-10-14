inherit M_COMMAND;

string *usage(void) {
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

   if (query_wizard(this_player())) {
      lines += ({ "\tinventory, junk, levels, score, skills, status, top" });
   } else {
      lines += ({ "\tinventory, junk, levels, score, skills, top" });
   }

   return lines;
}

static void main(string str) {
   string line;
   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   line = this_player()->get_status(this_player());
   write(line);
}
