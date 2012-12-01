void usage() {
   write("Usage: chfn [-h] [real YOURNAME | email EMAIL]\n");
   write("Allows you to change your basic information.\n");
   write("You can set your realname to YOURNAME or your email to EMAIL.\n");
   write("If no info is given show your current information.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\tchfn real Kent Mein\n");
   write("\tchfn email mein@cs.umn.edu\n");
   write("See also: passwd");
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
