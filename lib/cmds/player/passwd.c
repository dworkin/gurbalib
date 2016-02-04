inherit M_COMMAND;

string *usage(void) {
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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "alias");
   add_also("player", "ansi");
   add_also("player", "clear");
   add_also("player", "describe");
   add_also("player", "ignore");

   add_also("admin", "coloradm");
}

static void main(string arg) {
   string who, passwd;

   if (!alsos) {
      setup_alsos();
   }

   if (arg && (arg != "")) {
      if (!query_admin(this_player())) {
         this_player()->more(usage());
         return;
      }
      if (sscanf(arg, "%s %s", who, passwd) == 2) {
         if (USER_D->player_exists(who) > 0) {
            if (USER_D->reset_password(who, passwd)) {
               write("Password for user: " + who + ", set to : " + 
                  passwd + "\n");
            }
         } else {
            write(who + " is not a real user.\n");
         }
      } else {
         this_player()->more(usage());
      }
      return;
   }

   if (query_guest(this_player())) {
      write("Guest accounts do not have passwords.\n");
   } else {
      call_other(this_user(), "change_passwd", "");
   }
}
