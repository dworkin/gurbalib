inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: ban [-h] [-s SITE] [PLAYER]" });
   lines += ({ " " });
   lines += ({ "Allows you to toggle banishment of  the specified player " +
      "PLAYER." });
   lines += ({ "Alternately if you use the -s flag you can ban/unban a site " +
      "SITE." });
   lines += ({ "If no Player or SITE is given it displays what is currently " +
      "banned." });
   lines += ({ "If you use the key word new for one or more of the address " +
      "fields, " });
   lines += ({ "new players will be banned." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tban sirdude" });
   lines += ({ "\tban -s 128.101.32.*" });
   lines += ({ "\tban -s 128.101.32.new" });
   lines += ({ "\tban -s new.new.new.new" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "forcequit");
   add_also("wiz", "halt");
   add_also("wiz", "heal");
   add_also("wiz", "muzzle");
   add_also("wiz", "zap");
}

void show_banned(void) {
   string *sites, info;
   int i, max;

   write("Sites Banned:\n");
   sites = SITEBAN_D->query_banned_sites();
   max = sizeof(sites);
   if (max < 1) {
      write("No sites currently banned.\n");
   }

   for (i = 0; i < max; i++) {
      info = SITEBAN_D->get_banned_info(sites[i]);
      if (!info) {
         info = "\n";
      }
      write("\t" + sites[i] + "\t" + info);
   }

   write("Players Banned:\n");
   sites = BANISH_D->query_banished_names();
   max = sizeof(sites);
   if (max < 1) {
      write("No Players currently banned.\n");
   }
   for (i = 0; i < max; i++) {
      info = read_file("/data/banished/" + sites[i]);
      if (!info) {
         info = "\n";
      }
      write("\t" + sites[i] + "\t" + info);
   }
}

void ban_site(string str) {
   if ((str == "127.*.*.*") || (str == "127.0.*.*") || (str == "127.0.0.*") ||
      (str == "127.0.0.1")) {
      write("Ban " + str + "?!? You must be kidding...\n");
      return;
   }
   if (strstr(str, " ") != -1) {
      write("Cannot include whitespace in banished names.");
      return;
   }

   if (SITEBAN_D->is_banned(str) || SITEBAN_D->is_newbanned(str)) {
      if (SITEBAN_D->unsiteban(str)) {
         this_player()->simple_action("$N $vunban the site: " + str + "\n");
      } else {
         write("Failed to unban site: " + str + "\n");
         write("\tTry ban -h for usage.\n");
      }
   } else {
      if (SITEBAN_D->siteban(str)) {
         this_player()->simple_action("$N $vban the site: " + str + "\n");
      } else {
         write("Failed to ban site: " + str + "\n");
         write("\tTry ban -h for usage.\n");
      }
   }
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      show_banned();
      return;
   }

   if (sscanf(str, "-s %s", str)) {
      ban_site(str);
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (strstr(str, " ") != -1) {
      write("Cannot include whitespace in banished names.");
      return;
   }

   if (query_admin(str) && !query_admin(this_player()->query_name())) {
      write("Wizards are not allowed to ban an admin.\n");
      return;
   } else if (this_player()->query_name() == str) {
      write("You may not ban yourself.\n");
   } else if (!USER_D->player_exists(str)) {
      write("No such player: " + str + " exists.\n");
      return;
   } else {
      if (BANISH_D->is_banished(str)) {
         if (BANISH_D->unbanish_name(str)) {
   	    this_player()->simple_action("$N $vunbanish " + str + ".\n");
         } else {
            write("Failed to unban user: " + str + "\n");
            write("\tTry ban -h for usage.\n");
         }
      } else {
         if (BANISH_D->banish_name(str)) {
   	    this_player()->simple_action("$N $vbanish " + str + ".\n");
         } else {
            write("Failed to ban user: " + str + "\n");
            write("\tTry ban -h for usage.\n");
         }
      }
   }
}
