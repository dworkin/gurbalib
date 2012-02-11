void usage() {
  write("Usage: sysmsg [-h] MSG\n");
  write("Send a message MSG to the system.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string msg){
  object *usr;
  int i;

  usr = USER_D->query_players();

  if (!msg || (msg == "")) {
     usage();
     return;
  } else if (sscanf(msg, "-%s",msg)) {
     usage();
     return;
  } else {
    for (i = 0; i < sizeof(usr); i++) {
      usr[i]->message("\n" + 
        "%^RED%^System Message from %^GREEN%^" + 
        capitalize(this_player()->query_name()) + 
        "%^RED%^ on %^WHITE%^" + ctime(time()) + "%^RED%^:%^RESET%^\n");
      usr[i]->message("\"" + msg + "\"");
    }
    write_file("/logs/sysmsg", capitalize(this_player()->query_name()) + 
       " on " + ctime(time()) + ": \"" + msg + "\"\n");
  }
}
