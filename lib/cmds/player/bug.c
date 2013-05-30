void usage() {
   string *lines;

   lines = ({ "Usage: bug [-h] SUBJECT" });
   lines += ({ "" });
   lines += ({ "Allows you to submit a bug to the system." });
   lines += ({ "We can't fix bugs unless we know about them." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tbug the rabbit hole does not work in newbieville" });
      lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tchan, echo, echoto, emote, rsay, shout, ssay, say, " +
         "sysmsg, tell, translate, whisper, wizcall" });
   } else {
      lines += ({ "\tchan, emote, rsay, say, shout, tell, whisper, " +
         "wizcall" });
   }
   if (query_admin(this_player())) {
      lines += ({ "\twall" });
   }

   this_player()->more(lines);
}

private static mapping msg;
private static mapping subject;
private static mapping ob;

void main(string str) {
   string player_name;

   if (!str || (str == "")) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!msg) {
      msg = ([]);
      subject = ([]);
      ob = ([]);
   }
   player_name = this_player()->query_Name();

   ob[player_name] = "/domains/required/rooms/bug_room"->present("board");
   if (!ob[player_name]) {
      write("Unable to locate the bug board. Tell a wizard.\n");
      return;
   }

   if (!str || (str == "")) {
      subject[player_name] = "[" +
	 this_player()->query_environment()->file_name() + "]";
   } else {
      subject[player_name] = str;
   }

   write(" \nPlease enter your text below.\n" +
      "'.' without quotes on a blank line to end. ~a to abort.\n" +
      "----------------------------------------------------------" +
      "--------------------\n");
   this_player()->input_to_object(this_object(), "enter_line");
   this_player()->set_editing(1);
   msg[player_name] = "";
}

void enter_line(string line) {
   string player_name;

   player_name = this_player()->query_Name();
   if ((line != ".") && (line != "**") && (line != "~a")) {
      if (!msg[player_name]) {
	 msg[player_name] = line + "\n";
      } else {
	 msg[player_name] = msg[player_name] + line + "\n";
      }
      this_player()->input_to_object(this_object(), "enter_line");
   } else {
      if (line == "~a") {
	 write(" \nMessage aborted.\n");
      } else {
	 ob[player_name]->add_message(player_name,
	    subject[player_name], msg[player_name]);
	 write(" \nBug report sent! Thank you.\n");
	 CHANNEL_D->chan_send_string("wiz",
	    player_name, "sends off a bug report.", 1);

      }
      this_player()->set_editing(0);
      this_player()->write_prompt();
      this_environment()->tell_room(this_player(), player_name +
	 " lets us all know how much the mud sucks.\n");
   }
}
