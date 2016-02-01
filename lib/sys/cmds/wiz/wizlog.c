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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "bug");
   add_also("player", "chan");
   add_also("player", "emote");
   add_also("player", "rsay");
   add_also("player", "say");
   add_also("player", "shout");
   add_also("player", "tell");
   add_also("player", "whisper");
   add_also("player", "wizcall");

   add_also("wiz", "echo");
   add_also("wiz", "echoto");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "translate");

   add_also("admin", "wall");
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

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
