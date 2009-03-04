void main( string str ) {
  object ob;

  ob = USER_D->find_player( str );
  if( ob ) {
      if( ob->is_player() == 1) {
         this_player()->simple_action( "$N $vbiff "+ob->query_name()+" off the game.\n" );
         ob->do_quit();
      }
  }
  else {
    write( "You can't seem to find " + str + ".\n" );
  }
}
