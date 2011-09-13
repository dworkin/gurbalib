void usage() {
  write("Usage: promote [-h] PLAYER [player|wiz|admin]\n");
  write("Promote is kind of a missnomer, this command is used to change,\n");
  write("the level of a given player, to the level you specify.\n");
  write("We hope that you will be promoting rather than demoteing players.\n");
  write("If a wiz directory does not exist it will be created.\n");
  write("Promoting a wizard or admin to a player will not remove their " +
     "wiz dir.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("Examples:\n");
  write("\tpromote sirdude admin\tMake sirdude an admin\n");
  write("\tpromote sirdude wiz\tMake sirdude a wizard\n");
  write("\tpromote sirdude player\tMake sirdude a normal player\n");
}

void main( string str ) {
  string who, what;

  if( !str || str == "" ) {
    usage();
    return;
  }
  
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }
  if (sscanf(str, "%s %s", who, what) != 2) {
     usage();
     return;
  }
  if (!USER_D->user_exists(who)) {
     write( "No such user: " + who + ".\n" );
     return;
  }

  if (this_player()->query_name() == who) {
     write("You can not promote yourself.\n");
     return;
  }

  if( !require_priv( "system" ) ) {
     write( "You need admin privileges to change someones level.\n" );
     return;
  } 
  what = lowercase(what);
  if (what == "admin") {
     SECURE_D->make_admin( who );
  } else if (what == "wiz" || what == "wizard") {
     SECURE_D->make_wizard( who );
  } else if (what == "player" || what == "mortal") {
     SECURE_D->make_mortal( who );
  } else {
     usage(); 
  }
}
