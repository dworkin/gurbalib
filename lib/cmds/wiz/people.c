void main( string str ) {
  object *usr;
  int i;
  mixed idle;

  usr = USER_D->query_users();

  for (i = 0; i < sizeof (usr); i++) {
    if( usr[i]->query_player() ) {
      idle = usr[i]->query_player()->query_idle();
    } else {
      idle = 0;
    }
    write( capitalize(usr[i]->query_player()->query_name()) + "\t" +
           query_ip_number(usr[i]) + "\t" +
           usr[i]->query_player()->query_environment()->query_brief() + " " +
           format_time( intp( idle ) ? idle : 0 ) + "\n");
  }
}

