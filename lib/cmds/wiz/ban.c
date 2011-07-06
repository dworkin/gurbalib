void usage() {
  write("Usage: ban [-h] [-s SITE] [PLAYER]\n");
  write("Allows you to banish the specified player PLAYER.\n");
  write("Alternately if you use the -s flag you can ban a site SITE.\n");
  write("If no Player or SITE is given it displays what is currently " +
    "banned.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("Examples:\n");
  write("\tban sirdude\n");
  write("\tban -s 128.101.32.*\n");
  write("See also: who, unban\n");
}

void show_banned() {
   string *sites, info;
   int i,max;

   write("Sites Banned:\n");
   sites = SITEBAN_D->query_banned_sites();
   max = sizeof(sites);
   if (max < 1) {
      write("No sites currently banned.\n");
   }
   for( i=0; i<max; i++) {
      info = read_file("/data/banished/" + sites[i]);
      write("\t" + sites[i] + "\t" + info +"\n");
   }
   write("Players Banned:\n");
   sites = SITEBAN_D->query_banished_names();
   max = sizeof(sites);
   if (max < 1) {
      write("No Players currently banned.\n");
   }
   for( i=0; i<max; i++) {
      info = read_file("/data/banished/" + sites[i]);
      write("\t" + sites[i] + "\t" + info + "\n");
   }
}

void ban_site( string str ) {
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
      write("Failed to ban site : " + str + "\n");
      write("\tTry ban -h for usage.\n");
   }
}

void main( string str ) {
   if(!str || str == "") {
     show_banned();
     return;
   }
   if (sscanf(str, "-s %s",str)) {
      ban_site(str);
      if( str == "127.*.*.*" || str == "127.0.*.*" || str == "127.0.0.*" || 
      str == "127.0.0.1" ) {
      write("Ban "+str+"?!? You must be kidding...\n");
      return;
   }
     return;
   }
   if (sscanf(str, "-%s",str)) {
     usage();
     return;
   }
   if( strstr( str, " " ) != -1 ) {
      write("Cannot include whitespace in banished names.");
      return;
   }
   if (query_admin(str) && !query_admin(this_player()->query_name())) {
      write("Wizards are not allowed to ban an admin.\n");
      return;
   } else if (this_player()->query_name() == str) {
      write("You may not ban yourself.\n");
   } else {
      if( BANISH_D->banish_name( str ) ) {
         this_player()->simple_action( "$N $vbanish "+str+".\n" );
      } else {
         write("Failed to ban user : " + str + "\n");
         write("\tTry ban -h for usage.\n");
      }
   }
}
