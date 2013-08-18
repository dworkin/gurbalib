inherit M_COMMAND;

void usage() {
   string *lines;

   lines =({ "Usage: quit [-h]" });
   lines += ({ "" });
   lines += ({ "This is how you leave the game." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tquit" });
   lines += ({ "See also:" });
   lines += ({ "\tattack, cast, eat, enter, follow, go, pray" });


   this_player()->more(lines);
}

static void main(string str) {
   if (str && (str != "")) {
      usage();
      return;
   }

   this_player()->do_quit();
}
