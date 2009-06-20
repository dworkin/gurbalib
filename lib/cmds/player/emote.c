/* void main( string str ) { */
  
/*   string spc; */
/*   spc = " "; */

/*   this_player()->simple_action( "-> $N " + str + "\n" ); */
/* } */

void main( string str ) {
  if (str != "") {
    if ( !this_player()->is_player() || query_wizard( this_player() ) ) {
      this_player()->query_environment()->tell_room( nil, capitalize(this_player()->query_name()) + " " + str) ;
    } else {
      this_player()->query_environment()->tell_room( nil, "-> " + capitalize(this_player()->query_name()) + " " + str);
    }
  }
}
