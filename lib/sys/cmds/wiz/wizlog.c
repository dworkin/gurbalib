inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: wizlog [-h] MSG" });
   lines += ({ " " });
   lines += ({ "Allows a wizard to tell other wizards what they " +
      "have been up to." });
   lines += ({ "Use it to explain what you have been working on." });
   lines += ({ "All wizards will see what has been recorded since they last " +
      "logged in." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\twizlog worked on the usage for wizard commands." });
   lines += ({ "See also:" });

   if (query_wizard(this_player())) {
      lines += ({ "\tbug, chan, echo, echoto, emote, rsay, say, shout, " +
         "ssay, sysmsg, tell, translate, whisper, wizcall" });
   }
   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   return lines;
}

static void main(string str) {

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   DID_D->add_entry(str);
}
