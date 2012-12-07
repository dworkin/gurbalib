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

void main(string str) {
   string bar, title;
   int i, exp, maxi;
   mixed width;

   if (str && str != "") {
      usage();
      return;
   }

   write("LEVEL:   EXP     : Title");

   width = this_player()->query_env("width");
   maxi = intp(width);
   if (maxi < 2)
      maxi = DEFAULT_WIDTH;

   bar = "";
   for (i = 0; i < maxi; i++) {
      bar += "-";
   }
   write(bar + "\n");

   for (i = 0; i < 20; i++) {
      exp = i * i * 2000;
      title = this_player()->query_level_title(i + 1);
      write((i + 1) + "\t" + exp + "\t\t" + title);
   }
}
