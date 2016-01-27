inherit M_COMMAND;

string *usage(void) {
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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "chan");
   add_also("player", "emote");
   add_also("player", "rsay");
   add_also("player", "say");
   add_also("player", "shout");
   add_also("player", "tell");
   add_also("player", "whisper");
   add_also("player", "wizcall");

   add_also("wiz", "echo");
   add_also("wiz", "echoto");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "translate");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
}
private static mapping msg;
private static mapping subject;
private static mapping ob;

static void main(string str) {
   string player_name, tmp;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (!msg) {
      msg = ([]);
      subject = ([]);
      ob = ([]);
   }

   player_name = this_player()->query_Name();

   tmp = DOMAINS_DIR + "/required/rooms/bug_room";
   ob[player_name] = tmp->present("board");
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
