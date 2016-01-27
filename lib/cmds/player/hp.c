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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "inventory");
   add_also("player", "junk");
   add_also("player", "levels");
   add_also("player", "score");
   add_also("player", "skills");
   add_also("player", "top");

   add_also("wiz", "status");
}

static void main(string str) {
   string line;

   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   line = this_player()->get_status(this_player());
   write(line);
}
