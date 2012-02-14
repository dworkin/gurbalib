void usage() {
  write("Usage: muzzle [-h] PLAYER\n");
  write("Muzzle a player so they can no longer shout.\n");
  write("If PLAYER is already muzzled it unmuzzles them.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  int val;
  object *usrs;
  object usr;

  if (!str || (str == "")) {
     write("You need to specify a player name.\n");
  } else {
     if (sscanf(str, "-%s",str)) {
        usage();
     } else if (usr = USER_D->find_player(str) ) {
	val = usr->toggle_muzzle();
        if (val) {
	   write(capitalize(str) + " muzzled.\n");
	   usr->message( "You have been muzzled by:" +
              this_player()->query_Name() + "\n");
        } else {
	   write(capitalize(str) + " unmuzzled.\n");
	   usr->message( "You have been unmuzzled by:" +
              this_player()->query_Name() + "\n");
        }
     } else {
        write("Who are you looking for?  I can't find: " + str + "!\n");
     }
  }
}

