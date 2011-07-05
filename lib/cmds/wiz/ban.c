void usage() {
  write("Usage: ban [-h] [PLAYERNAME|SITE]\n");
  write("Allows you to banish the specified player and or site.\n");
  write("If no Player or SITE is given it displays what is currently " +
    "banned.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("Examples:\n");
  write("\tban sirdude\n");
  write("\tban 128.101.32.*\n");
}

void show_banned() {
   string *sites, info;
   int i;

   write("Sites Banned:\n");
   sites = SITEBAN_D->query_banned_sites();
   for( i=0; i<sizeof(sites); i++) {
      info = read_file("/data/banished/"+site);
      write("\t" + sites[i] + "\t" + info +"\n");
   }
   write("Players Banned:\n");
   sites = SITEBAN_D->query_banished_names();
   for( i=0; i<sizeof(sites); i++) {
      info = read_file("/data/banished/"+site);
      write("\t" + sites[i] + "\t" + info + "\n");
   }
}

void main( string str ) {
   if(!str || str == "") {
     show_banned();
     return;
   }
   if (sscanf(str, "-%s",str)) {
     usage();
     return;
   }
   if( str == "127.*.*.*" || str == "127.0.*.*" || str == "127.0.0.*" || 
      str == "127.0.0.1" ) {
      write("Ban "+str+"?!? You must be kidding...\n");
      return;
   }
   if( strstr( str, " " ) != -1 ) {
      write("Cannot include whitespace in banished names.");
      return;
   }
   if( SITEBAN_D->siteban(str) ) {
      this_player()->simple_action( "$N $vban the site: "+str+"\n" );
   } else {
      if (query_admin(str) && !query_admin(this_player->query_name()) {
         write("Wizards are not allowed to ban an admin.\n");
         return;
      } else if (this_player()->query_name() == str) {
         write("You may not ban yourself.\n);
      } else {
         if( BANISH_D->banish_name( str ) ) {
            this_player()->simple_action( "$N $vbanish "+str+".\n" );
         } else {
            usage();
         }
      }
   }
}
