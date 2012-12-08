void usage() {
   string *lines;

   lines = ({ "Usage: passwd [-h]" });
   lines += ({ "" });
   lines += ({ "Allows you to change your password." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpasswd" });
   lines += ({ "See also:" });
   lines += ({ "\talias, ansi, chfn, describe, ignore" });

   if (query_admin(this_player()) {
      lines == ({ "\tcoloradm" });
   }

   this_player()->more(lines);
}

void main(string arg) {
   if (arg && arg != "") {
      usage();
      return;
   }

   call_other(this_user(), "change_passwd", "");
}
