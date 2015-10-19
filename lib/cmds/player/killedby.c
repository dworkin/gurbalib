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
   lines += ({ "See also:" });
   lines += ({ "\tscore" });

   return lines;
   this_player()->more(lines);
}

static void main(string str) {
   string *lines;

   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   lines = this_player()->summarise_killers();
   this_player()->more(lines);
}

