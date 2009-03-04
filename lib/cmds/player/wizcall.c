void main (string str){
  int i;
  int flag;
  object *usrs;
  flag = 0;

  usrs = USER_D->query_users();
  if (str != "") {
    for (i = 0; i < sizeof(usrs); i++){
      if (SECURE_D->query_wiz(usrs[i]->query_player()->query_name()) > 0) {
	usrs[i]->query_player()->message("%^RED%^" + "" + capitalize(this_player()->query_name()) + " wizcalls: %^RESET%^" + str + "\n");
	write_file( "/logs/wizcall", capitalize(this_player()->query_name()) + " on " + ctime(time()) + ": " + str + "\n");
      }
    }
  } else {
    write ("The almighty wizards would like a reason for your attempting to summon them.");
    flag = 1;
  }
  if (flag == 0) {
    write ("You call for help.");
  }
}
