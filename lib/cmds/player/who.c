inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: who [-h] [PLAYER]" });
   lines += ({ "" });
   lines += ({ "Print out a list of who is on the system." });
   lines += ({ "If PLAYER is specified, give detailed info about the player." 
      });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\twho" });
   lines += ({ "\twho sirdude" });
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, look, mudlist, possess, rwho, " +
         "snoop, where" });
   } else {
      lines += ({ "\tlook" });
   }

   this_player()->more(lines);
}

/* 'who' command Originally by Fudge Improved by Cerihan 3/15/09 */
static void main(string str) {
   object *usr;
   int long_flag;
   string *out;

   if (query_wizard(this_player())) {
      long_flag = 1;
   } else {
      long_flag = 0;
   }

   if (!empty_str(str)) {
      if (sscanf(str, "-%s", str)) {
         usage();
         return;
      }

      if (USER_D->player_exists(str)) {
         USER_D->finger(this_player(), str);
      } else {
         write(capitalize(str) + " exists only in your dreams.\n");
      }

      return;
   }

   out = ({ horizontal_rule(this_player(), "-") });
   out += USER_D->list_players(long_flag);
   out += ({ horizontal_rule(this_player(), "-") });
   this_player()->more(out, 1);
}
