inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: chfn [-h] [KEY VALUE]" });
   lines += ({ "" });
   lines += ({ "Allows you to change your basic information." });
   lines += ({ "Valid KEY's are: email, realname, website" });
   lines += ({ "If no info is given show your current information." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tchfn realname Kent Mein" });
   lines += ({ "\tchfn email mein@cs.umn.edu" });
   lines += ({ "\tchfn website http://www.cs.umn.edu/~mein" });
   lines += ({ "See also:" });
   lines += ({ "\talias, ansi, clear, describe, ignore, passwd" });

   if (query_admin(this_player())) {
      lines += ({ "\tcoloradm" });
   }

   this_player()->more(lines);
}

static void show_chfn(void) {
   write("Email: " + this_player()->query_email_address() + "\n");
   write("Realname: " + this_player()->query_real_name() + "\n");
   write("Website: " + this_player()->query_website() + "\n");
}

static void main(string str) {
   string cmd, what;

   if (empty_str(str)) {
      if (query_guest(this_player()->query_name())) {
         write("chfn does not work with guest accounts.\n");
         return;
      }

      show_chfn();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!USER_D->player_exists(this_player()->query_name())) {
      write("chfn does not work with guest accounts.\n");
      return;
   }

   if (sscanf(str, "%s %s", cmd, what) != 2) {
      usage();
      return;
   }

   cmd = lowercase(cmd);
   if (cmd == "email") {
      this_player()->set_email_address(what);
      show_chfn();
   } else if (cmd == "real" || cmd == "realname") {
      this_player()->set_real_name(what);
      show_chfn();
   } else if (cmd == "website" || cmd == "web") {
      this_player()->set_website(what);
      show_chfn();
   } else {
      usage();
   }
}
