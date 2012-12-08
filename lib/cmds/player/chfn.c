void usage() {
   string *lines;

   lines = ({ "Usage: chfn [-h] [real YOURNAME | email EMAIL]" });
   lines += ({ "" });
   lines += ({ "Allows you to change your basic information." });
   lines += ({ "You can set your realname to YOURNAME or your email to EMAIL."
      });
   lines += ({ "If no info is given show your current information." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tchfn real Kent Mein" });
   lines += ({ "\tchfn email mein@cs.umn.edu" });
   lines += ({ "See also:" });
   lines += ({ "\talias, ansi, describe, ignore, passwd" });

   if (query_admin(this_player())) {
      lines += ({ "\tcoloradm" });
   }

   this_player()->more(lines);
}

void show_chfn() {
   write("Email: " + this_player()->query_email_address() + "\n");
   write("Real Name: " + this_player()->query_real_name() + "\n");
}

void main(string str) {
   string cmd, what;

   if (!str || str == "") {
      show_chfn();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }
   if (sscanf(str, "%s %s", cmd, what) != 2) {
      usage();
      return;
   }
   if (cmd == "email") {
      this_player()->set_email_address(what);
      show_chfn();
   } else if (cmd == "real") {
      this_player()->set_real_name(what);
      show_chfn();
   } else {
      usage();
   }
}
