void main( string str ) {
   object ob;

   ob = this_player()->query_environment()->present( str );
   if( ob ) {
      if( ob->is_player() ) {
         this_player()->simple_action( "$N $vtry to dest a player, and $vfail miserably.\n" );
      } else {
         this_player()->simple_action( "$N $vtouch the " + ob->query_id() + ", and it disappears.\n" );
         if( ob->query_environment() ) {
            ob->query_environment()->remove_object( ob );
         }
         ob->destruct();
      }
   }
   else if( this_player()->present( str ) ) {
      ob = this_player()->present( str );
      if( ob ) {
         if( ob->is_player() ) {
            this_player()->simple_action( "$N $vtry to dest a player, and $vfail miserably.\n" );
         }
         else {
            this_player()->simple_action( "$N $vtouch the " + ob->query_id() + ", and it disappears.\n" );
            if( ob->query_environment() ) {
               ob->query_environment()->remove_object( ob );
            }
            ob->destruct();
         }
      } 
   }
   else {
      write( "You can't seem to find the " + str + ".\n" );
   }
}
