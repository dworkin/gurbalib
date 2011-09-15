string subject;
string *to;
string msgdate;
string *body;

// XXX make it so admin can email ALL and it will send an email to all players.

void usage() {
  if (query_admin( this_player() ) ) {  // Give the 'all' syntax to admin's
     write("Usage: mail [-h] [all|PLAYER1 [PLAYER2] [...]]\n");
     write("Send a mud mail to the players specified.\n");
     write("You may also use all to send a mudmail to all players.\n");
     write("If no player is given check your mail to see if you have " +
        "any incomming messages.\n");
     write("Inside of the mail command you have the following options.\n");
     write("\td #\tDelete message #\n");
     write("\tm PLAYER\tSend a  message to PLAYER\n");
     write("\tm all\tSend a  message to all players\n");
     write("\tl \tView your mail.\n");
     write("\tq \tQuit.\n");
     write("Options:\n");
     write("\t-h\tHelp, this usage message.\n");
     write("See also: say, tell, whisper, emote\n");
  } else {
     write("Usage: mail [-h] [PLAYER1] [PLAYER2]]\n");
     write("Send a mud mail to the players specified.\n");
     write("If no player is given check your mail to see if you have " +
        "any incomming messages.\n");
     write("Inside of the mail command you have the following options.\n");
     write("\td #\tDelete message #\n");
     write("\tm PLAYER\tSend a  message to PLAYER\n");
     write("\tl \tView your mail.\n");
     write("\tq \tQuit.\n");
     write("Options:\n");
     write("\t-h\tHelp, this usage message.\n");
     write("See also: say, tell, whisper, emote\n");
  }
}

void view_mailbox(string str) {
   mixed *messages;
   int x, max;
   string cmd, what;

   if (!str || str == "") {
   } else if (str == "q" || str == "quit") {
   } else {
      if (sscanf(str,"%s %s",cmd, what) != 2) {
         write("Commands: d # (delete message) m player (mail player)  " +
            "l (list inbox) q (quit)\n");
         this_player()->input_to_object(this_object(), "view_mailbox");
         return;
      }
      if (cmd == "d" || cmd == "del" || cmd == "delete") {
         // MAIL_D->delete_message(this_player()->query_name(), what);
      }
      if (cmd == "m" || cmd == "mail") {
        to = explode(what, " ");
        write("Subject: ");
        this_player()->input_to_object(this_object(), "get_subject");
      }
   }

   // messages = MAIL_D->get_messages(this_player()->query_name());
   max = sizeof(messages);

   for (x=0;x<max;x++) {
   //    write(x + "\t" + messages[x]->query_subject() + "(" +
   //       messages[x]->query_from() + ")\n";
   }
   if (max < 1) {
      write("You have no mail!\n");
   }

   write("Commands: d # (delete message) m player (mail player)  " +
      "l (list inbox) q (quit)\n");
   this_player()->input_to_object(this_object(), "view_mailbox");
}

void get_subject(string str) {
   if (!str || str == "") {
      write("Subject: ");
      this_player()->input_to_object(this_object(), "get_subject");
   }

}

void main( string str ) {
   if (!str || str == "") {
	view_mailbox("");
   }
   if (sscanf(str, "-%s",str)) {
      usage();
      return;
   }

   if (str == "all") {
      if (query_admin( this_player() ) ) {

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
   this_player()->input_to_object(this_object(), "get_subject");
}
