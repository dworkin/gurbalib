inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: extinguish [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Turn off, or extinguish the specified object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\textinguish torch" });
   lines += ({ "\textinguish lamp" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, identify, light, list, listen, look, " +
      "search, sell, value" });

   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who"
         });
   }

   this_player()->more(lines);
}

static void main(string str) {
	usage();
}

