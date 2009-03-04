void main( string str ) {
  object *usr;
  int i;

  usr = USER_D->query_users();

  for (i = 0; i < sizeof (usr); i++) {
    write( capitalize(usr[i]->query_player()->query_name()) + "\t" + 
           query_ip_number(usr[i]) + "\t" +
           usr[i]->query_player()->query_environment()->query_brief() + " " + 
           format_time(usr[i]->query_player()->query_idle()) + "\n");
  }
}
