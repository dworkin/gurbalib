void main( string str ) {
   if(!str) {
      write("Ban which site? ( example: 1.2.*.* )\n");
      return;
   }
   if( str == "35.8.*.*" || str == "152.*.*.*" ) {
      write("Ban "+str+"?!? You must be kidding...\n");
      return;
   }
   if( SITEBAN_D->siteban(str) ) {
      this_player()->simple_action( "$N $vban the site: "+str+"\n" );
   } else {
      write("Bad ban format, please try again.\n");
   }
}
