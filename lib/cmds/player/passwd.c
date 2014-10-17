inherit M_COMMAND;

void usage() {
   string *lines;

   if (query_admin(this_player())) {
      lines = ({ "Usage: passwd [-h] [PLAYER PASSWORD]" });
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

   if (query_admin(this_player())) {
      lines += ({ "\tpasswd sirdude bingo" });
   }

   lines += ({ "See also:" });
   lines += ({ "\talias, ansi, chfn, clear, describe, ignore" });

   if (query_admin(this_player())) {
      lines += ({ "\tcoloradm" });
   }

   this_player()->more(lines);
}

static void main(string arg) {
   string who, passwd;

   if (arg && (arg != "")) {
      if (!query_admin(this_player())) {
         usage();
         return;
      }
      if (sscanf(arg,"%s %s",who,passwd) == 2) {
         if (USER_D->player_exists(who) > 0) {
            if (USER_D->reset_password(who,passwd)) {
	       write("Password for user: " + who + ", set to : " + 
                  passwd + "\n");
            }
         } else {
            write(who + " is not a real user.\n");
         }
      } else {
         usage();
      }
      return;
   }

   if (USER_D->player_exists(this_player()->query_name()) > 0) {
      call_other(this_user(), "change_passwd", "");
   } else {
      write("Guest accounts do not have passwords.\n");
   }
}
