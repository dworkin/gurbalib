void usage() {
   write("Usage: unban [-h] [-s SITE] [PLAYER]\n");
   write("Allows you to remove a banished player/site from the list of " +
      "banned players/sites.\n");
   write("If no Player or SITE is given it displays what is currently " +
      "banned.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\tunban sirdude\n");
   write("\tunban -s 128.101.32.*\n");
   write("See also: who, ban\n");
}

void show_banned() {
   string *sites, info;
   int i, max;

   write("Sites Banned:\n");
   sites = SITEBAN_D->query_banned_sites();
   max = sizeof(sites);
   if (max < 1) {
      write("No sites currently banned.\n");
   }
   for (i = 0; i < max; i++) {
      info = read_file("/data/banished/" + sites[i]);
      write("\t" + sites[i] + "\t" + info + "\n");
   }
   write("Players Banned:\n");
   sites = SITEBAN_D->query_banished_names();
   max = sizeof(sites);
   if (max < 1) {
      write("No players currently banned.\n");
   }
   for (i = 0; i < max; i++) {
      info = read_file("/data/banished/" + sites[i]);
      write("\t" + sites[i] + "\t" + info + "\n");
   }
}

void main(string str) {
   if (!str || str == "") {
      show_banned();
      return;
   }
   if (sscanf(str, "-s %s", str)) {
      if (SITEBAN_D->unsiteban(str)) {
	 this_player()->simple_action("$N $vunban " + str + "\n");
      } else {
	 write("Failed to unban site: " + str + "\n");
	 write("Try unban -h for usage.\n");
      }
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (BANISH_D->unbanish_name(str)) {
      this_player()->simple_action("$N $vunban " + str + "\n");
   } else {
      write("Failed to unban: " + str + "\n");
      write("Try unban -h for usage.\n");
   }
}
