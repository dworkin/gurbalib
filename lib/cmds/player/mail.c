inherit M_COMMAND;

string subject;
string *to;
string msgdate;
string *body;

string *usage(void) {
   string all, *lines;

   if (query_admin(this_player())) {
      lines = ({  "Usage: mail [-h] [all|PLAYER1 [PLAYER2] [...]]" });
      all = "\tm all\tSend a message to all players";
   } else {
      lines = ({ "Usage: mail [-h] [PLAYER1] [PLAYER2]]" });
   }

   lines += ({ " " });
   lines += ({ "Send a mud mail to the players specified." });
   lines += ({ "You may also use all to send a mudmail to all players." });
   lines += ({ "If no player is given check your mail to see if you have " +
      "any incoming messages." });
   lines += ({ "Inside of the mail command you have the following options." });
   lines += ({ "\td #\tDelete message #" });
   lines += ({ "\tm PLAYER\tSend a message to PLAYER" });

   if (all) {
      lines += ({ all });
   }

   lines += ({ "\tl \tView your mail." });
   lines += ({ "\tq \tQuit." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tmail" });
   lines += ({ "\tmail sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "delete");
   add_also("player", "look");
   add_also("player", "post");
   add_also("player", "read");
}

void delete_message(string str) {
   int x;

   if (sscanf(str, "%d", x)) {

/* XXX do the work here... delete(x); ... parse_range() would be good here. */

   } else {
      write("You need to enter a message number to delete.\n");
      this_player()->input_to_object(this_object(), "view_mailbox");
   }
}

void show_menu(void) {
   write("Commands: d # (delete message) m player (mail player)  " +
      "l (list inbox) q (quit)\n");
   this_player()->input_to_object(this_object(), "view_mailbox");
}

void send_message(string str) {
   if (!str || (str == "")) {
      write("Send Message? (Y|N):");
   }
   if ((str == "y") || (str == "Y")) {
      /* Send the message. */
   } else if ((str == "n") || (str == "N")) {
      show_menu();
   } else {
      send_message("");
   }
}

void get_subject(string str) {
   if (!str || (str == "")) {
      write("Subject: ");
      this_player()->input_to_object(this_object(), "get_subject");
   }

   subject = str;

/* XXX  body = editor results? */

   send_message("");
}

void continue_mail(string str) {
   if (!str || (str == "")) {
      write("Do you want to continue? (Y|N):");
   }
   if ((str == "y") || (str == "Y")) {
      get_subject("");
   } else {
      show_menu();
   }
}

void verify_to(string str) {
   int x, max, error;

   if (!str || (str == "")) {
      write("To: ");
      this_player()->input_to_object(this_object(), "verify_to");
   } else {
      error = 0;
      if (str == "all") {
         if (query_admin(this_player())) {
            to = USER_D->list_all_users();
         } else {
            write("You are not an admin you may not send an " +
               "email to everyone.\n");
            return;
         }
      } else {
         verify_to(str);
         x = 0;
         max = sizeof(to);
         while (x < max) {
            if (USER_D->player_exists(to[x])) {
               x = x + 1;
            } else {
               write("invalid user: to[x], removing...\n");
               to[x] = "";
               error = 1;
            }
         }
      }
      if (error) {
         write("You had some invalid users.\nSending mail to : ");
         x = 0;
         while (x < max) {
            write(to[x] + " ");
         }
         continue_mail("");
      }
   }
}

void view_mailbox(string str) {
   mixed *messages;
   int x, max;
   string cmd, what;

   if (!str || (str == "")) {
   } else if ((str == "q") || (str == "quit")) {
      write("Thank you for using mudmail!\n");
      return;
   } else if ((str == "d") || (str == "del") || (str == "delete")) {
      write("What message # do you want to delete:");
      this_player()->input_to_object(this_object(), "delete_message");
   } else if ((str == "l") || (str == "list") || (str == "list inbox")) {
      view_mailbox("");
   } else if ((str == "m") || (str == "mail")) {
      verify_to("");
   } else {
      if (sscanf(str, "%s %s", cmd, what) != 2) {
         show_menu();
         return;
      }
      if ((cmd == "d") || (cmd == "del") || (cmd == "delete")) {
         delete_message(what);
      }
      if ((cmd == "m") || (cmd == "mail")) {
         verify_to(what);
      }
   }

   /* messages = MAIL_D->get_messages(this_player()->query_name()); */
   if (messages) {
      max = sizeof(messages);
   } else {
      max = 0;
   }

   for (x = 0; x < max; x++) {
      write(x + "\t" + messages[x]->query_subject() + "(" +
         messages[x]->query_from() + ")\n");
   }
   if (max < 1) {
      write("You have no mail!\n");
   }

   show_menu();
}

static void main(string str) {

   if (!alsos) {
      setup_alsos();
   }

   write("XXX The mail command is still under construction.\n");
   this_player()->more(usage());
   return;

   if (empty_str(str)) {
      show_menu();
   } else {
      if (sscanf(str, "-%s", str)) {
         this_player()->more(usage());
         return;
      }

      verify_to(str);
   }
}
