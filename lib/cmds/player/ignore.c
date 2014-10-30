inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: ignore [-h] [PLAYER]" });
   lines += ({ "" });
   lines += ({ "Allows you to ignore a given player PLAYER," });
   lines += ({ "or stop ignoring them if they are currently ignored." });
   lines += ({ "If PLAYER is missing, show a list of who you are ignoring." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tignore sirdude" });
   lines += ({ "See also:" });
   lines += ({ "\talias, ansi, chfn, clear, describe, passwd" });

   if (query_admin(this_player())) {
      lines += ({ "\tcoloradm" });
   }

   this_player()->more(lines);
}

/* Add a user to your ignore list  -- Arron Cusimano (mordain) 20090321 */
static void main(string arg) {
   string out;
   int i, sz;
   string *list;

   if (empty_str(arg)) {
      out = "Ignored list:\n";
      list = this_player()->query_ignored_all();
      for (i = 0, sz = sizeof(list); i < sz; ++i)
	 out += list[i] + "\n";
      write(out);
      /*write(dump_value(this_player()->query_ignored_all(), ([]))); */
      return;
   }
   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }
   if (this_player()->query_ignored(arg)) {
      write("Removing " + arg + "\n");
      this_player()->remove_ignore(arg);
      return;
   }
   write("Ignoring " + arg + "\n");
   this_player()->add_ignore(arg);
}
