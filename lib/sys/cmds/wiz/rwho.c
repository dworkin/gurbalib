inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: rwho [-h] MUDNAME" });
   lines += ({ " " });
   lines += ({ "Remote who, lists users on another mud." });
   lines += ({ "To see what other muds you can look at use the command: " +
      "mudlist" });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\t rwho gurbalib" });
   lines += ({ "See also:" });
   lines += ({ "\tlast, locate, look, mudlist, possess, snoop, where, who" });

   this_player()->more(lines);
}

static void main(string str) {

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   IMUD_D->do_who(str);
}
