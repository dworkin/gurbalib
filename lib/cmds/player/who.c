/* void main( string str ) { */
/*   object *usr; */
/*   int i; */

/*   usr = USER_D->query_users(); */
/*   out( "Users online: " + sizeof(usr) + "\n" ); */
/*   for( i = 0; i < sizeof( usr ); i++ ) { */
/*     out( " " + capitalize(usr[i]->query_name()) + (usr[i]->query_player()->query_title()) + "\n" ); */
/*   } */
/* } */

void main( string str ) {
  object *usr;
  int i;

  usr = USER_D->query_users();
  if (SECURE_D->query_wiz(this_player()->query_name()) > 0 ) {
    for( i = 0; i < sizeof( usr ); i++) {
      if (SECURE_D->query_wiz(usr[i]->query_player()->query_name()) > 0 ) {
	write( "%^RED%^[WIZ] %^RESET%^" + capitalize(usr[i]->query_player()->query_title() + "\n"));
      }
    }
    write("------------------------------------------------------------------------------\n");
    for( i = 0; i < sizeof( usr ); i++) {
      if (!SECURE_D->query_wiz(usr[i]->query_player()->query_name()) ) {
	write( capitalize(usr[i]->query_player()->query_title() + "\n"));
      }
    }
  } else {
    for (i = 0; i < sizeof( usr); i++) {
      if (!SECURE_D->query_wiz(usr[i]->query_player()->query_name()) ) {
	write( capitalize(usr[i]->query_player()->query_title()) + "\n");
      }
    }
  }
}