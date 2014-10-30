inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: motd [-h]" });
   lines += ({ "" });
   lines += ({ "Allows you to view the motd(Message of the day)." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tmotd" });
   lines += ({ "See also:" });
   lines += ({ "\tfortune" });

   this_player()->more(lines);
}

static void main(string str) {
   if (empty_str(str)) {
      string *lines;

      lines = explode(TELNET_D->query_motd(), "\n");
      this_player()->more(lines);
   } else {
      usage();
   }
}
