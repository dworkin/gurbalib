inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: levels [-h]" });
   lines += ({ "" });
   lines += ({ "Displays a list of the various levels and requirements." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlevels" });
   lines += ({ "See also:" });
   lines += ({ "\thp, inventory, score, skills" });

   this_player()->more(lines);
}

static void main(string str) {
   string bar, title;
   int i, exp, width;

   if (str && (str != "")) {
      usage();
      return;
   }

   write("LEVEL:   EXP     : Title");

   width = this_player()->query_width();

   bar = "";
   for (i = 0; i < width; i++) {
      bar += "-";
   }
   write(bar + "\n");

   for (i = 0; i < 20; i++) {
      exp = i * i * 2000;
      title = this_player()->query_level_title(i + 1);
      write((i + 1) + "\t" + exp + "\t\t" + title);
   }
}
