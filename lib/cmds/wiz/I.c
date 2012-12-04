void usage() {
   string *lines;
   lines = ({ "Usage: I [-h] MSG" });
   lines += ({ " " });
   lines += ({ "Allows a wizard to tell other wizards what they " +
      "have been upto." });
   lines += ({ "Use it to explain what you have been working on." });
   lines += ({ "All wizards will see whats been recorded since they last " +
      "logged in." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tI worked on the usage for wizard commands." });
   lines += ({ "See also:" });
   lines += ({ "\tbug" });

   this_player()->more(lines);
}

void main(string str) {
   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   DID_D->add_entry(str);
}
