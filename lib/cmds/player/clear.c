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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "alias");
   add_also("player", "ansi");
   add_also("player", "clear");
   add_also("player", "describe");
   add_also("player", "ignore");
   add_also("player", "passwd");
}

static void main(string str) {
   int max, i;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      max = this_player()->query_height();
      str = "\n";
      for (i = 0; i < max; i++) {
         str += "\n";
      }
      write(str);
      return;
   } else {
      this_player()->more(usage());
      return;
   }
}
