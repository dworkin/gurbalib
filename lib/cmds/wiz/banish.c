void main( string str ) {
   if(!str) {
      write("Banish whom?\n");
      return;
   }
   if( str == "woodie" || str == "stubbs" || str == "fudge" ) {
      write("Banish "+str+"?!? You must be kidding...\n");
      return;
   }
   BANISH_D->banish_name(str);
   this_player()->simple_action( "$N $vbanish "+str+".\n" );
}
