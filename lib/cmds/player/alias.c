void usage() {
   write("Usage: alias [-h] [STR COMMAND]\n");
   write("Allows you to create an alias for a command.\n");
   write("If no alias is given show a list of your current aliases.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Example:\n");
   write("\talias ga get all\n");
}

void main(string str) {
   mapping alias;
   string *aliases;
   string cmd, arg;
   string *lines;
   int i;

   if (!str || str == "") {
      alias = this_player()->query_aliases();
      aliases = map_indices(alias);

      lines = ({ "You have defined these aliases: " });
      if (sizeof(aliases) == 0) {
	 lines += ({ "   You have no personal aliases defined." });
         lines += ALIAS_D->show_alias("","");
         this_player()->more(lines);
	 return;
      }

      if (sscanf(str, "-%s", str)) {
	 usage();
	 return;
      }

      lines = ({ "You have defined these aliases: " });
      for (i = 0; i < sizeof(aliases); i++) {
	 lines +=({ "  " + aliases[i] + "='" + alias[aliases[i]] + "'" });
      }

      lines += ALIAS_D->show_alias("","");
      this_player()->more(lines);

   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else {
      if (sscanf(str, "%s %s", cmd, arg) != 2) {
	 if (this_player()->is_alias(str)) {
	    /* Remove an alias */
	    write("Alias '" + str + "' (" + this_player()->query_alias(str) +
	       ") removed.");
	    this_player()->remove_alias(str);
	    return;
	 }

	 usage();
	 return;
      }

      this_player()->add_alias(cmd, arg);
      write("Alias '" + cmd + "' (" + arg + ") added.");
   }
}
