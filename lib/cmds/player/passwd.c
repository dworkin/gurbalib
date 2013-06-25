void usage() {
   string *lines;

   if (query_admin(this_player())) {
      lines = ({ "Usage: passwd [-h] [player]" });
   lines += ({ "" });
   lines += ({ "Allows you to change your password, or the password" });
   lines += ({ " of the specified player." });
   } else {
      lines = ({ "Usage: passwd [-h]" });
   lines += ({ "" });
   lines += ({ "Allows you to change your password." });
   }
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpasswd" });
   lines += ({ "See also:" });
   lines += ({ "\talias, ansi, chfn, describe, ignore" });

   if (query_admin(this_player())) {
      lines += ({ "\tcoloradm" });
   }

   this_player()->more(lines);
}

void main(string arg) {
   object obj;
   if (arg && (arg != "")) {
      obj = USER_D->find_player(arg);
      if (obj) {
         write("That user is currently logged in you cannot change their " +
            "password.\n");
      } else {
/* XXX Need to try to load the user and change their password. */
         usage();
         return;
      }
   }

   call_other(this_user(), "change_passwd", "");
}
