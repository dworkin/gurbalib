void main( string msg){
  object *usr;
  int i;

  usr = USER_D->query_users();

  if ((msg) !=  "") {
    for (i = 0; i < sizeof(usr); i++) {
      usr[i]->query_player()->message("\n" + "%^RED%^System Message from %^GREEN%^" + capitalize(this_player()->query_name()) + "%^RED%^ on %^WHITE%^" + ctime(time()) + "%^RED%^:%^RESET%^\n");
      usr[i]->query_player()->message(msg);
    }
    write_file("/logs/sysmsg", capitalize(this_player()->query_name()) + " on " + ctime(time()) + ": " + msg + "\n");
  }
}
