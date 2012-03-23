void usage() {
   write("Usage: ignore [-h] [PLAYER]\n");
   write("Allows you to ignore a given player PLAYER,\n");
   write("or stop ignoring them if they are currently ignored.\n");
   write("If PLAYER is missing, show a list of who you are ignoring.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

/* Add a user to your ignore list  -- Arron Cusimano (mordain) 20090321 */
void main(string arg) {
   string out;
   int i, sz;
   string *list;

   if (arg == "") {
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
