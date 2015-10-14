inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: light [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Turn on, or light the specified object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlight torch" });
   lines += ({ "\tlight lamp" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, extinguish, identify, list, listen, look, " +
      "search, sell, value" });

   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who"
         });
   }

   return lines;
}

static void main(string str) {
   this_player()->more(usage());
}

