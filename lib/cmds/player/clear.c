inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: clear [-h]" });
   lines += ({ "" });
   lines += ({ "Clear your screen." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tclear" });
   lines += ({ "See also:" });
   lines += ({ "\talias, ansi, chfn, clear, describe, ignore, passwd" });

   return lines;
   this_player()->more(lines);
}

static void main(string str) {
   int max, i;

   if (empty_str(str)) {
      max = this_player()->query_height();
      str = "\n";
      for (i=0; i < max; i++) {
         str += "\n";
      }
      write(str);
      return;
   } else {
      this_player()->more(usage());
      return;
   }
}
