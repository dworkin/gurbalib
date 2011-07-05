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

   SITEBAN_D->unsiteban(str);
   this_player()->simple_action( "$N $vunban "+str+"\n" );

// XXX  Need to add logic for player unban as well....
}
