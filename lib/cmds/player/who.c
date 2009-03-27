/* void main( string str ) { */
/*   object *usr; */
/*   int i; */

/*   usr = USER_D->query_users(); */
/*   out( "Users online: " + sizeof(usr) + "\n" ); */
/*   for( i = 0; i < sizeof( usr ); i++ ) { */
/*     out( " " + capitalize(usr[i]->query_name()) + (usr[i]->query_player()->query_title()) + "\n" ); */
/*   } */
/* } */

/*
  'who' command
  Originally by Fudge
  Improved by Cerihan 3/15/09
*/

void main( string str ) {
  object *usr;
  int i;
  usr = players();
  
  write(MUD_NAME + " currently has " + sizeof( usr ) + " users online."); 
  write("------------------------------------------------------");
  for( i = 0; i < sizeof( usr ); i++) {
    string line;
    line = capitalize(usr[i]->query_title());
    if ( SECURE_D->query_admin(usr[i]->query_name()) > 0 ) {
      line += " %^BOLD%^%^BLUE%^(Admin)%^RESET%^";
    }
    else if ( SECURE_D->query_wiz(usr[i]->query_name()) > 0 ) {
      line += " %^CYAN%^(Wizard)%^RESET%^";
    }
    write(line + "\n");
  }
  write("------------------------------------------------------");
}

