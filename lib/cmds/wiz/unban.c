void main( string str ) {
   if(!str) {
      write("Unban which site? ( Format: *.*.*.* )\n");
      return;
   }
   SITEBAN_D->unsiteban(str);
   this_player()->simple_action( "$N $vunban "+str+"\n" );
}
