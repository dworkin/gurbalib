inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: add_bonus [-h] STATNAME" });
   lines += ({ " " });
   lines += ({ "Increase your bonus to stat STATNAME by 1." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "See also:" });
   lines += ({ "\tadd_base, score, stats" });

   return lines;
}

static void main(string statname) {

   if (empty_str(statname)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(statname, "-%s", statname)) {
      this_player()->more(usage());
      return;
   }

   this_player()->add_bonus_stat(statname, 1);
   write("done!\n");
}
