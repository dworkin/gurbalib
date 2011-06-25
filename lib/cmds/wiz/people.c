void usage() {
  write("Usage: people [-h]\n");
  write("Print out a list of who is on the system, showing:\n");
  write("\tWhere they are logged in from.\n");
  write("\tWhere they are on the mud.\n");
  write("\tTheir idle time.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

// XXX  this and who need to be worked out...
//      I think its good to show idle in the standard who
//      not so keen on showing ip address maybe check to see players level
//      and show ip if they are a wiz or admin only....
//      would be nice to reduce commands....  could also make it
//      an optional flag only for wizards....
//      example: who -l 

void main( string str ) {
  object *usr;
  int i;
  mixed idletime;
  string idle;

  if (str && str != "") {
     usage();
     return;
  }

  usr = USER_D->query_users();

  for (i = 0; i < sizeof (usr); i++) {
    if( usr[i]->query_player() ) {
      idletime = format_time(usr[i]->query_player()->query_idle());
      if (idletime == "")  {
        idle = "";
      } else {
        idle = "  (idle " + idletime + ")";
      }
    } else {
      idle = "";
    }
    write( capitalize(usr[i]->query_player()->query_name()) + " (" +
           query_ip_number(usr[i]) + ")\t" +
           usr[i]->query_player()->query_environment()->query_brief() + 
           idle + "\n");
  }
}

