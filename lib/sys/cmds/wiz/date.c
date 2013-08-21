inherit M_COMMAND;
void usage() {
   string *lines;

   lines = ({ "Usage: date [-h]" });
   lines += ({ " " });
   lines += ({ "Show the real world time and date." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdate" });
   lines += ({ "See also:" });
   lines += ({ "\tscan, status, time" });

   this_player()->more(lines);
}

static void main(string str) {
   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (str && (str != "")) {
      usage();
      return;
   }

   write(ctime(time()) + "\n");
}
