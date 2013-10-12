inherit M_COMMAND;

void usage() {
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


   this_player()->more(lines);
}

int get_height() {
   int height;
   mixed height_env;
   
   height = (int)this_player()->query_env("height");
   if (height < 1) {
      height = 23;
   }
   return height;
}

static void main(string str) {
   int max, i;

   if (empty_str(str)) {
      max = get_height();
      str = "\n";
      for(i=0; i < max; i++) {
         str += "\n";
      }
      write(str);
      return;
   } else {
      usage();
      return;
   }
}
