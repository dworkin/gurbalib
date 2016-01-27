inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: killedby [-h]" });
   lines += ({ "" });
   lines += ({ "Summarise your deaths.." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tkilledby" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "score");
}

static void main(string str) {
   string *lines;

   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   lines = this_player()->summarise_killers();
   this_player()->more(lines);
}

