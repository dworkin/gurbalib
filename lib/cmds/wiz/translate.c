void usage() {
   string *lines;

   lines = ({ "Usage: translate [-h] WORD" });
   lines += ({ " " });
   lines += ({ "translate WORD into the catfolk language." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tXXX I'm broken get a wiz to fix me..." });
   lines += ({ "See also:" });
   lines += ({ "\tbug, echo, echoto, emote, rsay, say, shout, " +
      "ssay, sysmsg, tell, whisper, wizcall" });

   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   this_player()->more(lines);
}

/* XXX THis needs work, shouldn't only do catfolk... */

void main(string str) {
   if (!str || str == "") {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   write(str + "\n");
   write(LANGUAGE_D->english_to_racial("catfolk", str));
}
