void usage() {
   write("Usage: translate [-h] WORD\n");
   write("translate WORD into the catfolk language.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("I'm broken get a wiz to fix me...\n");
   write("See also: bug, emote, rsay, say, shout, ssay, tell, whisper, " +
      "wizcall\n");
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
