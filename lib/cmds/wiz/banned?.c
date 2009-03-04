void main( string site ) {
   string info;
   if( SITEBAN_D->is_banned(site) ) {
      info = read_file("/data/banished/"+site);
      write("The site '"+site+"' was banned:\n"+"\t"+info+"\n");
   } else {
      write("The site: "+site+" is NOT a banned site.\n");
   }
}
