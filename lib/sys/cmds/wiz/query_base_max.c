inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: query_base_max [-h] [STAT]" });
   lines += ({ " " });
   lines += ({ "Get the maximum base for stat STAT." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tquery_base_max strength" });
   lines += ({ "See also:" });
   lines += ({ "\tadd_base, add_bonus, score, stats" });

   this_player()->more(lines);
}

static void main(string str) {

   if (empty_str(str)) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   write("base_stat_maximum = " +
      this_player()->query_race_object()->query_base_stat_maximum(str) + "\n");
   write("done!\n");
}
