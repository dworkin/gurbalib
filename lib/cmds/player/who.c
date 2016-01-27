inherit M_COMMAND;

string *usage(void) {
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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "look");
   add_also("wiz", "last");
   add_also("wiz", "locate");
   add_also("wiz", "mudlist");
   add_also("wiz", "possess");
   add_also("wiz", "rwho");
   add_also("wiz", "snoop");
   add_also("wiz", "where");
}

/* 'who' command Originally by Fudge Improved by Cerihan 3/15/09 */
static void main(string str) {
   object *usr;
   int long_flag;
   string *out;

   if (!alsos) {
      setup_alsos();
   }


   if (query_wizard(this_player())) {
      long_flag = 1;
   } else {
      long_flag = 0;
   }

   if (!empty_str(str)) {
      if (sscanf(str, "-%s", str)) {
         this_player()->more(usage());
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
