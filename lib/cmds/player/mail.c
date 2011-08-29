string subject;
string *to;
string msgdate;
string *body;

// XXX make it so admin can email ALL and it will send an email to all players.

void usage() {
  if (query_admin( this_player() ) {
     write("Usage: mail [-h] [PLAYER1 [PLAYER2] [...]]\n");
     write("Send a mud mail to the players specified.\n");
     write("You may also use all to send a mudmail to all players.\n");
     write("If no player is given check your mail to see if you have " +
        "any incomming messages.\n");
     write("Options:\n");
     write("\t-h\tHelp, this usage message.\n");
     write("See also: say, tell, whisper, emote\n");
  } else {
     write("Usage: mail [-h] [PLAYER]\n");
     write("Send a mud mail to the players specified.\n");
     write("If no player is given check your mail to see if you have " +
        "any incomming messages.\n");
     write("Options:\n");
     write("\t-h\tHelp, this usage message.\n");
     write("See also: say, tell, whisper, emote\n");
  }
}

void view_mailbox() {
}

void get_subject() {
   if (!str || str == "") {
      write("Subject: ");
      input_to("get_subject");
   }

}

void main( string str ) {
   if (!str || str == "") {
	view_mailbox();
   }
   if (sscanf(str, "-%s",str)) {
      usage();
      return;
   }

   if (str == "all") {
      if (query_admin( this_player() ) {

// XXX need to set to to all valid users...

      } else {
         write("You are not an admin you may not send an email to everyone.\n");
	 return;
      }
   } else {
      to = explode(str, " ");
      if (!to) {
         to[0] = str;
      }
      // XXX Check to see if memebers of to are valid users...
   }

   write("Subject: ");
   input_to("get_subject");
}
