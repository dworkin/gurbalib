void main( string str ) {
   if(!str) {
      write("Unbanish whom?\n");
      return;
   }
   BANISH_D->unbanish_name(str);
   this_player()->simple_action( "$N $vunbanish "+str+".\n" );
}
